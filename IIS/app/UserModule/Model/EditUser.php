<?php
namespace App\UserModule\Model;
use Nette;
use App\LoginModule\Model\MyAuthenticator;

final class  EditUser
{
	use Nette\SmartObject;
	private $database;
	private MyAuthenticator $MyAuthenticator;

	public function __construct(Nette\Database\Explorer $database,MyAuthenticator $MyAuthenticator) 
	{
		$this->database = $database;
		$this->MyAuthenticator = $MyAuthenticator;
	}

	public function getProfileData(string $username)
	{
		return $this->database->fetch('SELECT * FROM uzivatel WHERE ID = ?', $username);
	}

	public function saveProfileData(string $username,\stdClass $values):void
	{
		$this->database->table('uzivatel')->get($username)->update([
			'meno' => $values->meno,
			'priezvisko' => $values->priezvisko,
			'telefon' => $values->telefon,
			'email' => $values->email,
			'mesto' => $values->mesto,
			'ulice' => $values->ulice,
			'psc' => $values->psc,
		]);
		if(isset($values->role))
		{
			$this->database->table('uzivatel')->get($username)->update([
				'role' => $values->role,]);
		}
		if($values->password)	
		{
			$this->MyAuthenticator->chengePass($username,$values->password);			
		}
	}
}