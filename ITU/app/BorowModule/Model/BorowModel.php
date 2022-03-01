<?php
 /**
 * @brief  dashboard 
 *
 * @authors Jakub Komárek (xkomar33)
 */
namespace App\BorowModule\Model;
use Nette;

final class  BorowModel
{
	use Nette\SmartObject;

	private $database;
	public function __construct(Nette\Database\Explorer $database) 
	{
		$this->database = $database;
	}

	public function getCars($values)
	{
		$rows= $this->database->table('car');
		$rows->where('seats >= ?', $values->mist);
		$rows->where('dojezd >= ?',intval($values->dojezd));

		switch ($values->prevodovka) 
		{
			case 'manual':
				$rows->where('prevodovka','Manuálna');	
				break;
			case 'automat':
				
				$rows->where('prevodovka','Automatická');
				break;
			default:
				break;
		}

		switch ($values->pohon) 
		{
			case 'spalovaci':
				$rows->where('drive','Diesel');	
				break;
			case 'elektricky':
				
				$rows->where('drive','Elektromobil');
				break;
			default:
				break;
		}
		return $rows->limit(9);
	}

	public function reservationAdd(int $idUser,int $idCar,$od,$do):void
	{
		$this->database->table('reservation')->insert([
			'ID_car' => $idCar,
			'ID_user' => $idUser,
			'datum_rezervacie' => $od,
			'datum_vratenia' => $do	
		]);
	}
}