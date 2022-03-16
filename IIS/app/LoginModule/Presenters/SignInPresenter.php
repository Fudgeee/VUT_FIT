<?php

declare(strict_types=1);

namespace App\LoginModule\Presenters;

use Nette;
use Nette\Application\UI\Form;

final class SignInPresenter extends \App\CoreModule\Presenters\BasePresenter
{
	public function beforeRender()
	{
		$this->mySession->lock = true;
		parent::beforeRender();
	}

	protected function createComponentSignInForm(): Form
	{
		$form = new Form;
		$form->addProtection();
		$form->addText('username', 'Login:')->setRequired('Zadejte login, prosím.');

		$form->addPassword('password', 'Heslo:')->setRequired('Zadejte heslo, prosím.');

		$form->addSubmit('send', 'Přihlásit');

		$form->onSuccess[] = [$this, 'signInFormSucceeded'];
		return $form;
	}

	public function signInFormSucceeded(Form $form, \stdClass $values): void
	{
		try 
		{
			$this->getUser()->login($values->username, $values->password);
			$this->getUser()->setExpiration('30 minutes');
			if($this->mySession->backlink)
				$this->restoreRequest($this->mySession->backlink);
			$this->redirect(':Core:Homepage:');

		} catch (Nette\Security\AuthenticationException $e) 
		{
			$form->addError('Nesprávné heslo nebo uživatelské jméno.');
		}
	}
}
