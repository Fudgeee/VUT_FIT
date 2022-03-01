<?php
 /**
 * @brief  dashboard 
 *
 * @authors Adrián Matušík (xmatus35)
 */
namespace App\DashBoardModule\Model;
use Nette;

final class  DashBoardModel
{
	use Nette\SmartObject;

	private $database;
	public function __construct(Nette\Database\Explorer $database) 
	{
		$this->database = $database;
	}
	public function getRezervation(int $userId)
	{
		return $this->database->table('reservation')->where('ID_user',$userId);
	}
	public function getRezervationById(int $id)
	{
		return $this->database->table('reservation')->get($id);
	}
	public function DeleteReservation(int $id)
	{
		$this->database->table('reservation')->get($id)->delete();
	}
	public function DeleteReservation1(int $id)
	{
		$this->database->table('reservation')->get($id)->delete();
	}
	public function LockLock(int $id)
	{
		$var =$this->database->table('car')->get($id);
		$var->update(['lock' => '0']);
	}
	public function UnlockLock(int $id)
	{
		$var =$this->database->table('car')->get($id);
		$var->update(['lock' => '1']);
	}
}