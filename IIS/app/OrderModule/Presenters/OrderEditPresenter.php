<?php

declare(strict_types=1);

namespace App\OrderModule\Presenters;
use App\OrderModule\Model\OrderModel;

use Nette;
use Nette\Application\UI\Form;

final class OrderEditPresenter extends  \App\CoreModule\Presenters\LogedPresenter
{
    protected function startup(): void
	{
		parent::startup();
		$this->operationAutorize('Orders','add');
	}

    private OrderModel $OrderModel;

	public function __construct(OrderModel $OrderModel)
	{
        $this->OrderModel=$OrderModel;
	}

	private $orderData;
	public function renderDefault(int $orderId): void
	{
		if(!$this->OrderModel->autetizateAcessToOrder($this->user,$orderId))
			$this->error("forbiden",403);

		$this->orderData=$this->OrderModel->getOrder($orderId);

		if(!$this->orderData)
			$this->error("objednávka nexistuje",403);

		$this->template->order= $this->orderData;	
        $this->template->items= $this->OrderModel->getItems($orderId);
	}

	protected function createComponentItemCreateForm(): Form
	{
		$form = new Form;
		$form->addHidden('ID')->setDefaultValue($this->orderData);
		$typ = $this->OrderModel->getTituls()->fetchPairs('ID','ID');   
        $form->addSelect('ID_titul', 'Titul:', $typ);
		$form->addInteger('mnozstvi', 'Množství:')->setDefaultValue(1)->addRule($form::MIN, 'Minimální množství je 1', 1);

		$form->addSubmit('submit', 'Přidat položku')->onClick[] = [$this, 'AddItem'];
		$form->addProtection();

		return $form;
	}

	protected function createComponentSendCreateForm(): Form
	{
		$form = new Form;
		$form->addHidden('ID');
		$form->addHidden('ID_knihovna');
		$form->setDefaults($this->orderData);
		$distributors= $this->OrderModel->getDistributors()->fetchPairs('ID');   
		foreach ($distributors as $distributor) 
		{
			$selectItems[$distributor->ID]=$distributor->meno." ".$distributor->priezvisko." (".$distributor->ID.")";	
		}

        $form->addSelect('ID_uzivatel_distr', 'Distributor:', $selectItems);

		$form->addSubmit('submit', 'Odeslat distributorovi')->onClick[] = [$this, 'SendOrder'];
		$form->addSubmit('delete', 'Smazat objednávku')->onClick[] = [$this, 'DeleteOrder'];
		$form->addProtection();

		return $form;
	}

	public function SendOrder(Form $form, \stdClass $values): void
	{

		$this->operationAutorize('Orders','add');
		if(!$this->OrderModel->autetizateAcessToOrder($this->user,intval($values->ID)))
			$this->error("forbiden",403);

		if(!$this->OrderModel->sendAutorization(intval($values->ID)))
		{
			$form->addError('Prázdná či již odeslaná objednávka nelze odeslat');
		}
		else
		{
			$this->OrderModel->sendOrder( intval($values->ID),$values->ID_uzivatel_distr);
			$this->redirect('Order:', intval($values->ID));
		}
	}
	public function DeleteOrder(Form $form, \stdClass $values): void
	{
		$this->operationAutorize('Orders','add');
		if(!$this->OrderModel->autetizateAcessToOrder($this->user,intval($values->ID)))
			$this->error("forbiden",403);

		if(!$this->OrderModel->addAutorization(intval($values->ID)))
		{
			$form->addError('Odeslaná objednávka nelze vymazat');
		}
		else
		{
			$this->OrderModel->deleteOrder( intval($values->ID));
			$this->redirect('Orders:', $values->ID_knihovna);
		}
	}
	public function AddItem(Form $form, \stdClass $values): void
	{
		$this->operationAutorize('Orders','add');
		if(!$this->OrderModel->autetizateAcessToOrder($this->user,intval($values->ID)))
			$this->error("forbiden",403);

		if(!$this->OrderModel->addAutorization(intval($values->ID)))
		{
			$form->addError('Nelze editovat odeslanou objednávku');
		}
		else
		{
			$this->OrderModel->addItem( intval($values->ID),$values);
		}
	}

	public function handleDeleteItem(int $orderId,string $idTitul): void
	{
		$this->operationAutorize('Orders','add');
		if(!$this->OrderModel->autetizateAcessToOrder($this->user,$orderId))
			$this->error("forbiden",403);

		if(!$this->OrderModel->addAutorization($orderId))
		{
			$this->flashMessage('Nelze editovat odeslanou objednávku');
			$this->redirect('Order:', $orderId);
		}
		else
		{
			$id=$this->OrderModel->deleteItem($orderId,$idTitul);
			$this->redirect('this');
		}	
	}

}
