<?php
/**
 * @brief  extended base presenter - base for secured parts of aplication
 *
 * @authors Jakub Komárek (xkomar33)
 */
namespace App\CoreModule\Presenters;

use Nette;
use App\Model;

class LogedPresenter extends \App\CoreModule\Presenters\BasePresenter
{
    protected function startup(): void
	{	
        if (!$this->getUser()->isLoggedIn()) 
        {
			if ($this->getUser()->getLogoutReason() === \Nette\Http\UserStorage::INACTIVITY) 
            {
				$this->flashMessage('Sesion vypršela');
                $this->redirect(':Login:SignIn:',['backlink' => $this->storeRequest()]);
			}
			$this->redirect(':Login:SignIn:');
		}
		parent::startup();		
	}
}

