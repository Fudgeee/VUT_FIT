<?php
/**
 * @brief editUser model
 *
 * @authors Adrián Matušík (xmatus35)
 */
namespace App\UserModule\Model;
use Nette;
use App\LoginModule\Model\MyAuthenticator;
use App\LoginModule\Model\DuplicateNameException;

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

	public function getProfileData(int $id)
	{
		return $this->database->table('user')->where('ID',$id)->fetch();
	}

	public function saveProfileData(int $id,\stdClass $values):void
	{
		try 
		{
			$this->database->table('user')->where('id', $id)->update([
				'name' => $values->name,
				'surname' => $values->surname,
				'phone' => $values->phone,
				'email' => $values->email,
				'town' => $values->town,
				'street' => $values->street,
				'pc' => $values->pc,
			]);
		} 
		catch (Nette\Database\UniqueConstraintViolationException $e) 
		{
			throw new DuplicateNameException;
		}

		if(isset($values->role))
		{
			$this->database->table('user')->get($id)->update([
				'role' => $values->role,]);
		}
		
		if($values->password)	
		{
			$this->MyAuthenticator->chengePass($id,$values->password);			
		}
		
	}
}