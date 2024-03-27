<?php
namespace App\LibraryModule\Model;

use Nette;
use Nette\Application\UI\Form;
use App\LoginModule\Model\DuplicateNameException;

final class  LibraryModel
{
	use Nette\SmartObject;
	private $database;

	public function __construct(Nette\Database\Explorer $database) 
	{
		$this->database = $database;
	}

	public function getLibraries()
	{
		return $this->database->table('knihovna');
	}

	public function getLibrary(string $library)
	{
		return $this->database->table('knihovna')->get($library);
	}

	public function getLibrariesAdm($identity)
	{
		if($identity->isInRole('admin'))
		{
			return $this->database->table('knihovna');
		}
		else
		{
			return $this->database->query('SELECT * from knihovna K, spravuje S WHERE S.ID_uzivatel = ? and  K.ID = S.ID_knihovna',$identity->getIdentity()->getId());
		}
	}

	public function getLibraryAdm($identity,string $library)
	{
		if($identity->isInRole('admin'))
			return $this->database->query('SELECT * from knihovna K WHERE K.ID = ? ',$library)->fetch();
		else
			return $this->database->query('SELECT * from knihovna K, spravuje S WHERE S.ID_uzivatel= ? and S.ID_knihovna= ? and  K.ID = S.ID_knihovna',$identity->getIdentity()->getId(),$library)->fetch();
	}

	public function getKnihovnik()
	{
		return $this->database->table('uzivatel')->where('role','knihovnik');
	}

	public function getKnihovniksInLib(string $library)
	{
		return $this->database->query('SELECT * from uzivatel K, spravuje S WHERE K.ID = S.ID_uzivatel  and S.ID_knihovna=?',$library);
	}

	public function addKnihovnik(string $library,string $login)
	{
		try 
		{
			$this->database->table('spravuje')->insert(['ID_uzivatel' => $login,
				'ID_knihovna' => $library
			]);
		} 
		catch (Nette\Database\UniqueConstraintViolationException $e) 
		{
			throw new DuplicateNameException;
		}
	}

	public function autetizateAcess($identity,string $library):bool
	{
		if($identity->isInRole('admin'))
			return true;
		if($this->database->query('SELECT * from knihovna K, spravuje S WHERE S.ID_uzivatel= ? and S.ID_knihovna= ? ',$identity->getIdentity()->getId(),$library)->getRowCount())
			return true;
		else
			return false;
	}

	public function saveLibaryData(string $libname,\stdClass $values):void
	{
		$this->database->table('knihovna')->get($libname)->update([
			'popis' => $values->popis,
			'adresa' => $values->adresa,
			'oteviraci_doba' => $values->oteviraci_doba,
		]);
	}

	public function addLibrary(string $name): void
	{
		try 
		{
			$this->database->table('knihovna')->insert(['ID' => $name]);
		} 
		catch (Nette\Database\UniqueConstraintViolationException $e) 
		{
			throw new DuplicateNameException;
		}
	}

	public function deleteLibary(string $name)
	{
		$this->database->table('knihovna')->where('ID', $name)->delete();;
	}

	public function deleteKnihovnik(string $libraryName,string $knihovnikId)
	{
		$this->database->table('spravuje')->where('ID_uzivatel', $knihovnikId)->where('ID_knihovna' ,$libraryName)->delete();;
	}

	public function libEditFormCreate(): Form
	{
		$form = new Form;
		$form->addHidden('ID');
		$form->addTextArea('popis', 'Popis')->addRule($form::MAX_LENGTH, 'Popis je příliš dlouhý', 2048);
		$form->addTextArea('oteviraci_doba', 'Otevírací doba')->addRule($form::MAX_LENGTH, 'Otevírací doba je příliš dlouhá', 1024);
		$form->addTextArea('adresa', 'Adresa')->addRule($form::MAX_LENGTH, 'Adresa je příliš dlouhá', 512);
		return $form;
	}
}