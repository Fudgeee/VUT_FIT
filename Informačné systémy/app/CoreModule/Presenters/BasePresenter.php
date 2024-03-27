<?php

namespace App\CoreModule\Presenters;

use Nette;
use App\Model;


class BasePresenter extends Nette\Application\UI\Presenter
{
    /** @var Nette\Http\SessionSection */
	public $mySession;


	protected function startup()
	{
		parent::startup();
		$this->mySession = $this->session->getSection("mySession");
	}

	public function beforeRender()
	{
		parent::beforeRender();
        if($this->mySession->lock)
            $this->mySession->lock=false;
        else
            $this->mySession->backlink = $this->storeRequest();
	}
    
    public function formatLayoutTemplateFiles():array
    {
        return [__DIR__ ."/templates/@layout.latte",];
    }

    public function handleLogout():void
    {
        $this->getUser()->logout(true);
        $this->flashMessage('Odhlšení proběhlo úspěšně');
        if($this->mySession->backlink)
			$this->restoreRequest($this->mySession->backlink);
        $this->redirect(':Core:Homepage:');
    }
}
