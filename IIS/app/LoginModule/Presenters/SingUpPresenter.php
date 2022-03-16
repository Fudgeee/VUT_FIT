<?php

declare(strict_types=1);

namespace App\LoginModule\Presenters;

use Nette;
use Nette\Application\UI\Form;
use App\LoginModule\Model\MyAuthenticator;
use App\LoginModule\Model\DuplicateNameException;

final class SignUpPresenter extends \App\CoreModule\Presenters\BasePresenter
{
	public function beforeRender()
	{
		$this->mySession->lock = true;
		parent::beforeRender();
	}

	private MyAuthenticator $MyAuthenticator;

	public function __construct(MyAuthenticator $MyAuthenticator)
	{
		$this->MyAuthenticator = $MyAuthenticator;
	}

	protected function createComponentSignUpForm(): Form
	{
		$form = new Form;
		$form->addProtection();
		$form->addText('username', 'Login:')->setRequired('Zadejte login, prosím.')->addRule($form::MAX_LENGTH, 'Uživatelské jméno je příliž dlouhé', 48);
		$form->addPassword('password', 'Heslo:')->setRequired('Zadejte heslo, prosím.')->addRule($form::MIN_LENGTH, 'Heslo musí mít alespoň %d znaků', 8);
		$form->addPassword('passwordVerify', 'Heslo znovu:')
			->setRequired('Zadejte prosím heslo ještě jednou pro kontrolu')
			->addRule($form::EQUAL, 'Hesla se neshodují', $form['password'])
			->setOmitted();
		$form->addSubmit('send', 'Registrovat');


		$form->onSuccess[] = [$this, 'signUpFormSucceeded'];
		return $form;
	}


	public function signUpFormSucceeded(Form $form, \stdClass $values): void
	{
		try 
		{
			$this->MyAuthenticator->add($values->username, $values->password);
			$this->getUser()->login($values->username, $values->password);
			$this->getUser()->setExpiration('30 minutes');
			$this->redirect(':User:UserEdit:');

		} catch (DuplicateNameException $e) 
		{
			$form->addError('Uživatel exituje, zvolte prosím jiný login');
		}		
	}
}
