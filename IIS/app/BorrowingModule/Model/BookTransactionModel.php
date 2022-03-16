<?php
namespace App\BorrowingModule\Model;
use App\LoginModule\Model\DuplicateNameException;
use Nette;

final class  BorrowingModel
{
	use Nette\SmartObject;
	private $database;

	public function __construct(Nette\Database\Explorer $database) 
	{
		$this->database = $database;
	}

	public function getBorrows(string $userName)
	{
		return $this->database->table('vypujcka')->where('ID_uzivatel',$userName)->order('ID DESC');
	}
	public function getBorrowsFromLib(string $libId)
	{
		return $this->database->query('SELECT V.*, U.meno,U.ID as username, U.priezvisko  FROM vypujcka V JOIN uzivatel U ON V.ID_uzivatel=U.ID  WHERE V.ID_knihovna=? ORDER BY V.ID DESC',$libId );
	}

	public function getBorrow(int $ID)
	{
		return $this->database->table('vypujcka')->where('ID',$ID)->fetch();
	}

	public function zamitnoutBorrow(int $ID)
	{
		$row=$this->database->table('vypujcka')->where('ID',$ID)->fetch();
		$ID_titul=$row->ID_titul;
		$ID_knihovna=$row->ID_knihovna;
		if($row->stav=="rezervováno"||$row->stav=="ve frontě")
		{
			$this->database->table('vypujcka')->where('ID',$ID)->update(['stav'=>'zamítnuto']);
			if($row->stav=="rezervováno")
			{
				$this->database->table('poskytuje')->where('ID_titul',$ID_titul)->where('ID_knihovna',$ID_knihovna)->update(['vydano-='=>1]);
				$this->queueUpdate($ID_titul,$ID_knihovna);
			}
		}
	}

	public function smazatBorrow(int $ID)
	{
		$row=$this->database->table('vypujcka')->where('ID',$ID)->fetch();
		$ID_titul=$row->ID_titul;
		$ID_knihovna=$row->ID_knihovna;
		if($row->stav=="rezervováno"||$row->stav=="ve frontě")
		{
			if($row->stav=="rezervováno")
			{
				$this->database->table('poskytuje')->where('ID_titul',$ID_titul)->where('ID_knihovna',$ID_knihovna)->update(['vydano-='=>1]);
				$this->queueUpdate($ID_titul,$ID_knihovna);
			}
			$this->database->table('vypujcka')->where('ID',$ID)->delete();
		}
	}

	public function vydatBorrow(int $ID)
	{
		$row=$this->database->table('vypujcka')->where('ID',$ID)->fetch();
		$ID_titul=$row->ID_titul;
		$ID_knihovna=$row->ID_knihovna;
		if($row->stav=="rezervováno")
		{
			$this->database->table('vypujcka')->where('ID',$ID)->update(['stav'=>'vydáno',
				'datum_vydano'=>date('Y-m-d H:i:s')
			]);
		}
	}

	public function vratitBorrow(int $ID)
	{
		$row=$this->database->table('vypujcka')->where('ID',$ID)->fetch();
		$ID_titul=$row->ID_titul;
		$ID_knihovna=$row->ID_knihovna;
		if($row->stav=="vydáno")
		{
			$this->database->table('vypujcka')->where('ID',$ID)->update(['stav'=>'vráceno',
				'datum_vraceno'=>date('Y-m-d H:i:s')
			]);
			$this->database->table('poskytuje')->where('ID_titul',$ID_titul)->where('ID_knihovna',$ID_knihovna)->update(['vydano-='=>1]);
			$this->queueUpdate($ID_titul,$ID_knihovna);
			$this->vratitEmptyCheck($ID_titul,$ID_knihovna);
		}
	}

	public function vratitVyraditBorrow(int $ID)
	{
		$row=$this->database->table('vypujcka')->where('ID',$ID)->fetch();
		$ID_titul=$row->ID_titul;
		$ID_knihovna=$row->ID_knihovna;
		if($row->stav=="vydáno")
		{
			$this->database->table('vypujcka')->where('ID',$ID)->update(['stav'=>'vráceno',
			'datum_vraceno'=>date('Y-m-d H:i:s')
			]);
			$this->database->table('poskytuje')->where('ID_titul',$ID_titul)->where('ID_knihovna',$ID_knihovna)->update(['vydano-='=>1,
				'mnozstvi-='=>1
			]);
			$this->vratitEmptyCheck($ID_titul,$ID_knihovna);
		}
	}
	public function vratitEmptyCheck(string $ID_titul, string $ID_knihovna)
	{
		$row=$this->database->table('poskytuje')->where('ID_titul',$ID_titul)->where('ID_knihovna',$ID_knihovna)->fetch();
		if($row->mnozstvi<1&&$row->vydano<1)
		{
			$this->database->table('poskytuje')->where('ID_titul',$ID_titul)->where('ID_knihovna',$ID_knihovna)->delete();
		}
	}
	public function queueUpdate(string $ID_titulu,string $ID_knihovna)
	{
		$rows=$this->database->table('vypujcka')->where('ID_titul',$ID_titulu)->where('ID_knihovna',$ID_knihovna)->where('stav','ve frontě');
		foreach($rows as $row)
		{
			$ID=$row->ID;
			$row2=$this->database->table('poskytuje')->where('ID_titul',$ID_titulu)->where('ID_knihovna',$ID_knihovna)->fetch();
			if($row2->vydano<$row2->mnozstvi)
			{
				$row2->update(['vydano+='=>1]);
				$this->database->table('vypujcka')->where('ID',$ID)->update(['stav'=>'rezervováno']);
			}
			else
				break;
		}
	}
	public function prodlouzitBorrow(int $ID):bool
	{
		$row=$this->database->table('vypujcka')->where('ID',$ID)->fetch();

		if($row->prodlouzeni<2)
		{
			$row->update(['prodlouzeni+='=>1]);
			return true;
		}
		return false;
	}

	public function accesBorrow($identity,int $ID):bool
	{
		if($identity->isInRole('admin'))
		{
			return true;
		}

		$row=$this->database->table('vypujcka')->where('ID',$ID)->fetch();
		if(!$row)
			return false;
		if($identity->isInRole('knihovnik'))
		{
			if($this->database->table('spravuje')->where('ID_uzivatel',$identity->getIdentity()->getId())->where('ID_knihovna',$row->ID_knihovna)->fetch())
			{
				return true;
			}
		}
		else if($identity->isInRole('registered'))
		{
			if($row->ID_uzivatel==$identity->getIdentity()->getId())
			{
				return true;
			}
		}
		return false;
	}

	public function autorizeLib($identity,string $libary):bool
	{
		if($identity->isInRole('admin'))
		{
			return true;
		}
		else if($identity->isInRole('knihovnik'))
		{
			if($this->database->table('spravuje')->where('ID_uzivatel',$identity->getIdentity()->getId())->where('ID_knihovna',$libary)->fetch())
			{
				return true;
			}
		}
		return false;
	}
}