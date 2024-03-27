<?php
 /**
 * @brief fullsystem model
 *
 * @authors Adrián Matušík (xmatus35)
 */
namespace App\FullSystemModule\Model;
use Nette;

final class  FullModel
{
	use Nette\SmartObject;

	private $database;
	public function __construct(Nette\Database\Explorer $database) 
	{
		$this->database = $database;
	}
	public function getUsers()
	{
		return $this->database->table('user');
	}
	public function getUser(int $id)
	{
		return $this->database->table('user')->get($id);
	}
	public function getCount()
	{
		$array['all']=$this->database->table('user')->count('*');
		return $array;
	}
	public function removeUser(int $id)
	{
		$this->database->table('user')->get($id)->delete();
	}
	public function userRoleSet(int $id,string $role)
	{
		$this->database->table('user')->get($id)->update(['role' => $role]);
	}
	public function verVer(int $id)
	{
		$var =$this->database->table('user')->get($id);
		$var->update(['verified' => '1']);
	}
	public function unverVer(int $id)
	{
		$var =$this->database->table('user')->get($id);
		$var->update(['verified' => '0']);
	}
}