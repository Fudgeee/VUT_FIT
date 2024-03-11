<?php
 /**
 * @brief  Manager model - práce s databázií
 * @authors Marián Backa (xbacka01)
 */
namespace App\ManagerModule\Model;
use Nette;

final class  ManagerModel
{
	use Nette\SmartObject;

	private $database;
	public function __construct(Nette\Database\Explorer $database) 
	{
		$this->database = $database;
	}

	/*Funkce vrací rezervace v závislosti na parametrech*/ 
	public function getReservations(int $page,string $orderBy,string $filtr,int $itemsPerPage)
	{
		switch ($filtr) {
			case 'waiting':
				$row=$this->database->table('reservation')->where('schvalene',0);
				break;
			case 'passed':
				$row=$this->database->table('reservation')->where('schvalene',1);
				break;
			case 'denied':
				$row=$this->database->table('reservation')->where('schvalene',2);
				break;
			case 'all':
				$row=$this->database->table('reservation');
				break;
			default:
				$row=$this->database->table('reservation');
				break;
		}

		switch ($orderBy) {
			case 'jmeno':
				$row=$row->order("ID_user.name");
				break;
			case 'jemenoDec':
				$row=$row->order("ID_user.name DESC");
				break;
			case 'prijmeni':			
				$row=$row->order("ID_user.surname");
				break;
			case 'prijmeniDec':
				$row=$row->order("ID_user.surname DESC");
				break;
			case 'auto':
				$row=$row->order("ID_car.brand");
				break;
			case 'autoDec':
				$row=$row->order("ID_car.brand DESC");
				break;
			case 'datumZ':
				$row=$row->order("datum_rezervacie");
				break;
			case 'datumZDec':
				$row=$row->order("datum_rezervacie DESC");
				break;
			case 'datumK':
				$row=$row->order("datum_vratenia");
				break;
			case 'datumKDec':
				$row=$row->order("datum_vratenia DESC");
				break;
			default:
				break;
		}
		


		$row->page($page, $itemsPerPage);

		return $row;


	}
	/*Funkce zmeni stav položky v tabluke na základe ID na schválený(1)*/
	public function reservationAccept(int $id)
	{
		$this->database->table('reservation')->get($id)->update([
			'schvalene' => 1, 
		]);
	}

	/*Funkce zmeni stav položky v tabluke na základe ID na zamítnut(2)*/
	public function reservationReject(int $id)
	{
		$this->database->table('reservation')->get($id)->update([
			'schvalene' => 2, 
		]);
	}


}