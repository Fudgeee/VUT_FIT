<?php
namespace App\BookTransactionModule\Model;
use App\LoginModule\Model\DuplicateNameException;
use Nette;

final class  BookTransactionModel
{
	use Nette\SmartObject;
	private $database;

	public function __construct(Nette\Database\Explorer $database) 
	{
		$this->database = $database;
	}

	public function getBooks(string $libName)
	{
		return $this->database->query('SELECT * FROM titul T, poskytuje P WHERE T.ID=P.ID_titul and P.ID_knihovna= ?',$libName);
	}
	public function getTituls()
	{
		return $this->database->table('titul');
	}
	public function addBook(string $libName,int $mnozstvi,string $titul)
	{
		if($this->database->table('poskytuje')->where('ID_knihovna',$libName)->where('ID_titul',$titul)->fetch())
		{
			$this->database->table('poskytuje')->where('ID_knihovna',$libName)->where('ID_titul',$titul)->update([
				'mnozstvi+=' =>  $mnozstvi,
			]);
		}
		else
		{
			$this->database->table('poskytuje')->insert(['ID_knihovna' => $libName,
				'ID_titul' => $titul,
				'mnozstvi' =>  $mnozstvi,
			]);
		}
	}

	public function getRowPoskytuje( string $libName,string $titul)
	{
		return $this->database->table('poskytuje')->where('ID_knihovna',$libName)->where('ID_titul',$titul)->fetch();
	}

	public function editBookN( string $libName,string $titul,int $mnozstvi)
	{
		$row=$this->database->table('poskytuje')->where('ID_knihovna',$libName)->where('ID_titul',$titul)->fetch();
		if($mnozstvi==0&&$row->vydano<1)
			$row->delete();
		else
		{
			$this->database->table('poskytuje')->where('ID_knihovna',$libName)->where('ID_titul',$titul)->update([
				'mnozstvi' =>  $mnozstvi,
			]);
		}		
	}

	public function autorize($identity,string $libary):bool
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