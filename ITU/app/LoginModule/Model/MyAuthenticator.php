<?php
/**
 * @brief  autentificator model
 *
 * @authors Jakub Komárek (xkomar33)
 */
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

	public function authenticate(string $email, string $password): SimpleIdentity
	{

		$row = $this->database->table('user')->where('email', $email)->fetch();
		if (!$row) 
		{
			throw new Nette\Security\AuthenticationException('User not found.');
		}

		if ( !$this->passwords->verify($password, $row->password)) 
		{
			throw new Nette\Security\AuthenticationException('Invalid password.');
		}

		return new SimpleIdentity( $row->ID,$row->role);
	}

	public function add(string $email, string $password,string $role="user"): void
	{
		try 
		{
			$this->database->table('user')->insert(['email' => $email,'password' => $this->passwords->hash($password),'role' => $role]);
		} 
		catch (Nette\Database\UniqueConstraintViolationException $e) 
		{
			throw new DuplicateNameException;
		}
	}

	public function chengePass(int $id, string $password): void
	{
		$this->database->table('user')->get($id)->update(['password' => $this->passwords->hash($password)]);
	}
}

class DuplicateNameException extends \Exception
{
}