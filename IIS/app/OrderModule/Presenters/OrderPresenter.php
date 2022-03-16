<?php

declare(strict_types=1);

namespace App\OrderModule\Presenters;
use App\OrderModule\Model\OrderModel;

use Nette;
use Nette\Application\UI\Form;

final class OrderPresenter extends  \App\CoreModule\Presenters\LogedPresenter
{
    protected function startup(): void
	{
		parent::startup();
		$this->resorceAutorize('OrderMix');
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

	public function handleVyridit($id)
	{
		$this->resorceAutorize('OrdersDView');
	
		if(!$this->OrderModel->autetizateAcessToOrder($this->user,intval($id)))
			$this->error("forbiden",403);
			
		$this->OrderModel->handleOrder(intval($id));
	}

}
