<?php

declare(strict_types=1);

namespace App\AdminModule\Presenters;

use App\AdminModule\Model\UserAdmPage;
use Nette;


final class UsersAdminPresenter extends  \App\CoreModule\Presenters\LogedPresenter
{
    protected function startup(): void
	{
		parent::startup();
		$this->resorceAutorize('AdminPage');
	}

	private UserAdmPage $admContoler;

	public function __construct(UserAdmPage $admContoler)
	{
        $this->admContoler=$admContoler;
	}


	public function renderDefault(): void
	{
		$this->template->users=$this->admContoler->getUsers();		
	}

}
