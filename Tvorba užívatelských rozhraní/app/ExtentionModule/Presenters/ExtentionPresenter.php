<?php
/**
 * @brief manager presenter
 *
 * @authors Jakub Komárek
 */
declare(strict_types=1);

namespace App\ExtentionModule\Presenters;

use App\ExtentionModule\Model\ExtentionModel;
use Nette\Forms\Controls\SubmitButton;

use Nette;
use Nette\Application\UI\Form;

final class ExtentionPresenter extends  \App\CoreModule\Presenters\LogedPresenter
{

    private ExtentionModel $DBM;
	public function __construct(ExtentionModel $DBM)
	{
        $this->DBM=$DBM;
	}

	protected function beforeRender()
    {

    }

	private function getTheWholeList(): array
	{
		return $this->DBM->getCars()->fetchAll();
	}

	public function renderDefault(): void
	{
		if (!$this->isAjax()) 
		{
			$this->template->list = $this->getTheWholeList();
			$this->template->stats= $this->DBM->getStats();
		}
	}

	public function handleChangeActive(int $id): void
	{
		$this->DBM->carTogle($id);
		$this->template->list = $this->isAjax()
				? []
				: $this->getTheWholeList();
				
		$this->template->list[$id] =  $this->DBM->getCar( $id);
		$this->redrawControl('itemsContainer');
		$this->template->stats= $this->DBM->getStats();
		$this->redrawControl('stats');

	}

	public function handleChangeClass(int $id,int $class): void
	{
		$this->DBM->carClassSet($id,$class);

		$this->template->list = $this->isAjax()
				? []
				: $this->getTheWholeList();
		$this->template->list[$id] =  $this->DBM->getCar( $id);
		$this->redrawControl('itemsContainer');

	}
	
	public function handleChangeStatusDisplay(int $id): void
	{
		$this->template->actionCar=$this->DBM->getCar( $id);

		$this->redrawControl('action');
	}

	public function handleChangeStatus(int $id,int $class): void
	{
		$this->template->list = $this->isAjax()
				? []
				: $this->getTheWholeList();

		$this->DBM->carStateSet( $id, $class);
		$this->template->actionCar=$this->DBM->getCar( $id);
		$this->template->list[$id] =  $this->DBM->getCar( $id);

		$this->redrawControl('actionSniped');
	}

	public function handleCloseStatusWin(int $id): void
	{
		$this->template->list = $this->isAjax()
				? []
				: $this->getTheWholeList();
				
		$this->template->list[$id] =  $this->DBM->getCar( $id);
		$this->redrawControl('itemsContainer');
		$this->redrawControl('action');
	}

	public function handleCloseDetails(): void
	{
		$this->redrawControl('details');
	}

	public function handleShowDetails(int $id): void
	{
		$this->template->details= $this->DBM->getCar($id);
		$this->redrawControl('details');
	}

	public function handleAdd(): void
	{
		$this->DBM->addCar();
		$this->template->list = $this->getTheWholeList();
		$this->redrawControl('wholeList');
		$this->template->stats= $this->DBM->getStats();
		$this->redrawControl('stats');
	}

	public function handleRemove(int $id): void
	{
		$this->DBM->removeCar($id);
		$this->template->list = $this->getTheWholeList();
		$this->redrawControl('wholeList');
		$this->template->stats= $this->DBM->getStats();
		$this->redrawControl('stats');

	}

	protected function createComponentEditCar(): Form
	{
		$form = new Form;

		$form->getElementPrototype()->class = 'ajax';
		$form->getElementPrototype()->id='my_form'; 
		$form->addText('brand', 'Jméno auta:')->addRule($form::MAX_LENGTH, 'Jméno auta je příliž dlouhé', 48);

		$form->addSelect('drive', 'Pohon:', ['Diesel'=>'Spalovací','Elektromobil'=>'Elektrický'])
			->setDefaultValue('Diesel');
		$form->addSelect('prevodovka', 'Převodovka:', ['Manuálna'=>'Manuální','Automatická'=>'Automatická'])
			->setDefaultValue('Manuálna');
		$form->addInteger('seats', 'Míst:')
			->setDefaultValue(1)
			->addRule($form::RANGE, 'Úroveň musí být v rozsahu mezi %d a %d.', [1, 100]);
			
		$form->addHidden('ID');
		$form->onSuccess[] = [$this, 'postFormSucceeded'];
		$form->addSubmit('Odeslat',"Uložit");//->onClick[] = [$this, 'postFormSucceeded'];

		if(isset($this->template->details)){
			$form->setDefaults($this->template->details);
			
		}
		
		return $form;
	}
	
	public function postFormSucceeded($form, $values) 
	{
		$this->DBM->editCar($values);

		$this->template->list = $this->isAjax()
				? []
				: $this->getTheWholeList();

		$this->template->list[$values->ID]	=$this->DBM->getCar( intval( $values->ID));

		$this->redrawControl("details");
		$this->redrawControl('itemsContainer');
		
	}

}	
