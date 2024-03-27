<?php
namespace App\BookModule\Model;
use App\LoginModule\Model\DuplicateNameException;
use Nette;

final class  BookFinder
{
	use Nette\SmartObject;
	private $database;

	public function __construct(Nette\Database\Explorer $database) 
	{
		$this->database = $database;
	}

	public function searchBooks(string $text, string $method="nazev")
	{
		if($method=="nazev")
			return $this->database->query('SELECT * FROM titul  WHERE ID REGEXP  ?', $text);
		else if($method=="zanr")
			return $this->database->query('SELECT * FROM titul  WHERE zanry REGEXP  ?', $text);
		else if($method=="tag")
			return $this->database->query('SELECT * FROM titul  WHERE tagy REGEXP  ?', $text);
		else
			return null;
	}
	
	public function listAll()
	{
		return $this->database->query('SELECT * FROM titul ');
	}

	public function addBook(string $name): void
	{
		try 
		{
			$this->database->table('titul')->insert(['ID' => $name]);
		} 
		catch (Nette\Database\UniqueConstraintViolationException $e) 
		{
			throw new DuplicateNameException;
		}
	}

	public function editBook(string $name,\stdClass $values):void
	{
		$this->database->table('titul')->get($name)->update([
			'popis' => $values->popis,
			'vydavatelstvo' => $values->vydavatelstvo,
			'zanry' => $values->zanry,
			'tagy' => $values->tagy,
			'datumVydani' => $values->datumVydani,
		]);
	}

	public function getBook(string $bookName)
	{
		return $this->database->table('titul')->get($bookName);
	}

	public function getAutors(string $bookName)
	{
		return $this->database->table('autor')->where('ID_titul',$bookName);
	}

	public function addAutor(string $bookName,\stdClass $values): void
	{
		$this->database->table('autor')->insert([
			'ID_titul' => $bookName,
			'meno' =>$values->meno,
			'priezvisko' =>$values->priezvisko,
		]);
	}

	public function voteBook(string $bookName,string $username): void
	{
		try 
		{
			$this->database->table('hlas')->insert([
				'ID_uzivatel' => $username,
				'ID_titul' =>$bookName,
			]);
		} 
		catch (Nette\Database\UniqueConstraintViolationException $e) 
		{
			throw new DuplicateNameException;
		}
	}

	public function getVoteCount(string $bookName):int
	{
		return $this->database->table('hlas')->where('ID_titul',$bookName)->count('*');
	}

	public function deleteAutor(string $bookName,int $discriminant)
	{
		$this->database->table('autor')->where('ID_titul', $bookName)->where('diskriminant',$discriminant)->delete();
	}

	public function deleteBook(string $name)
	{
		$this->database->table('titul')->where('ID', $name)->delete();;
	}

	public function getBorrows(string $id)
	{
		return $this->database->table('poskytuje')->where('ID_titul',$id);
	}

	public function zarezervovat(string $libName,string $bookName,string $username)
	{
		$this->database->table('vypujcka')->insert(['ID_knihovna'=>$libName,
			'ID_titul'=>$bookName,
			'ID_uzivatel'=>$username,
			'datum_vytvoreno'=>date('Y-m-d H:i:s')
		]);
	}	
}