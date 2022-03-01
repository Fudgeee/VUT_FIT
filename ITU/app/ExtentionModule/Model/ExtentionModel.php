<?php
 /**
 * @brief  Extention module
 * @authors Jakub Komárek
 */
namespace App\ExtentionModule\Model;
use Nette;

final class  ExtentionModel
{
	use Nette\SmartObject;

	private $database;
	public function __construct(Nette\Database\Explorer $database) 
	{
		$this->database = $database;
	}

	public function getCars()
	{
		return $this->database->table('car');
	}

	public function getCar(int $id)
	{
		return $this->database->table('car')->get($id);
	}

	public function carTogle(int $id)
	{
		$var =$this->database->table('car')->get($id);
		if($var->active)
			$var->update(['active' => '0']);
		else
			$var->update(['active' => '1']);
	}

	public function carClassSet(int $id,int $class)
	{
		$this->database->table('car')->get($id)->update(['class' => $class]);
	}

	public function carStateSet(int $id,int $state)
	{
		$this->database->table('car')->get($id)->update(['state' => $state]);
	}

	public function addCar()
	{
		$this->database->table('car')->insert([
			'brand' => 'auto '. strval($this->database->table('car')->count('*')),
		]);
	}

	public function removeCar(int $id)
	{
		$this->database->table('car')->get($id)->delete();
	}

	public function editCar($data)
	{
		$this->database->table('car')->get($data->ID)->update([
			'brand' => $data->brand,
			'drive' => $data->drive,
			'prevodovka' => $data->prevodovka,
			'seats' => $data->seats,
		]);
	}

	public function getStats()
	{
		$array['all']=$this->database->table('car')->count('*');
		$array['active']=$this->database->table('car')->where('active',1)->count('*');
		$array['passive']=$array['all']-$array['active'];
		$array['ocupied']=4;
		$array['free']=$array['all']-$array['ocupied']-$array['passive'];
		return $array;
	}
}