<?php
/**
 * @brief  base presenter - base for nonsecured parts of aplication
 *
 * @authors Jakub Komárek (xkomar33)
 */
namespace App\CoreModule\Presenters;

use Nette;
use App\Model;


class BasePresenter extends Nette\Application\UI\Presenter
{

    protected function startup(): void
	{	
		parent::startup();		
	}

    protected function beforeRender()
    {
        $this->redrawControl('title');
        $this->redrawControl('content');

    }

    public function formatLayoutTemplateFiles():array
    {
        return [__DIR__ ."/templates/@layout.latte",];
    }

    public function handleLogout():void
    {
        $this->getUser()->logout(true);
        $this->flashMessage('Odhlášení proběhlo úspěšně');
        $this->redirect(':Login:SignIn:');
    }
}
