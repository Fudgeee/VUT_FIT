<?php
/**
 * @brief  signIn presenter
 *
 * @authors Jakub Komárek (xkomar33)
 */
declare(strict_types=1);

namespace App\LoginModule\Presenters;

use Nette;
use Nette\Application\UI\Form;

final class SignInPresenter extends \App\CoreModule\Presenters\BasePresenter
{
	protected function startup(): void
	{	
        if ($this->getUser()->isLoggedIn()) 
        {
			$this->redirect(':DashBoard:DashBoard:');
		}
		parent::startup();		
	}
	
	protected function beforeRender()
	{
		parent::beforeRender();
		$this->redrawControl('nav');
	}

	protected function createComponentSignInForm(): Form
	{
		$form = new Form;
		$form->addProtection();
		$form->addText('email')->setRequired('Zadejte email, prosím.')->setHtmlAttribute('placeholder','Email');

		$form->addPassword('password', )->setRequired('Zadejte heslo, prosím.')->setHtmlAttribute('placeholder','Heslo');

		$form->addSubmit('send', 'Přihlásit');

		$form->onSuccess[] = [$this, 'signInFormSucceeded'];
		
		return $form;
	}

	public function signInFormSucceeded(Form $form, \stdClass $values): void
	{
		try 
		{
			$this->getUser()->login($values->email, $values->password);
			$this->getUser()->setExpiration('30 minutes');
			$this->redirect(':DashBoard:DashBoard:default',true);
		}
		catch (Nette\Security\AuthenticationException $e) 
		{
			$this->flashMessage('Nesprávné přihlašovací údaje','error');
		}
	}
}
