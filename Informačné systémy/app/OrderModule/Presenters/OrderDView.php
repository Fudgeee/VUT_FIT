<?php

declare(strict_types=1);

namespace App\OrderModule\Presenters;
use App\OrderModule\Model\OrderModel;

use Nette;
use Nette\Application\UI\Form;

final class OrderDViewPresenter extends  \App\CoreModule\Presenters\LogedPresenter
{
    protected function startup(): void
	{
		parent::startup();
		$this->resorceAutorize('OrdersDView');
	}

    private OrderModel $OrderModel;

	public function __construct(OrderModel $OrderModel)
	{
        $this->OrderModel=$OrderModel;
	}

	public function renderDefault(): void
	{		
		if($this->getUser()->isInRole('admin'))
			$this->template->orders=$this->OrderModel->getOrdersAll();
		else
			$this->template->orders=$this->OrderModel->getOrdersForDistr($this->user->getIdentity()->getId());
	}
}
