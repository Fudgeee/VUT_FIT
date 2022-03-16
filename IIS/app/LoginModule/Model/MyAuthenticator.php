<?php
namespace App\LoginModule\Model;

use Nette;
use Nette\Security\SimpleIdentity;

class MyAuthenticator implements Nette\Security\Authenticator
{
	use Nette\SmartObject;
	private $database;
	private $passwords;

	public function __construct(Nette\Database\Explorer $database,Nette\Security\Passwords $passwords) 
	{
		$this->database = $database;
		$this->passwords = $passwords;

	}

	public function authenticate(string $username, string $password): SimpleIdentity
	{

		$row = $this->database->table('uzivatel')->where('ID', $username)->fetch();
		if (!$row) 
		{
			throw new Nette\Security\AuthenticationException('User not found.');
		}

		if ( !$this->passwords->verify($password, $row->heslo)) 
		{
			throw new Nette\Security\AuthenticationException('Invalid password.');
		}

		return new SimpleIdentity( $row->ID,$row->role);
	}

	public function add(string $username, string $password,string $role='registered'): void
	{
		try 
		{
			$this->database->table('uzivatel')->insert(['ID' => $username,'heslo' => $this->passwords->hash($password),'role' => $role]);
		} 
		catch (Nette\Database\UniqueConstraintViolationException $e) {
			throw new DuplicateNameException;
		}
	}

	public function chengePass(string $username, string $password): void
	{
		$this->database->table('uzivatel')->get($username)->update(['heslo' => $this->passwords->hash($password)]);
	}
}
class DuplicateNameException extends \Exception
{
}