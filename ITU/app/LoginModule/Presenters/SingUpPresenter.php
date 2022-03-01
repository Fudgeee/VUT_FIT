<?php
/**
 * @brief  signUp presenter
 *
 * @authors Jakub Komárek (xkomar33)
 */
declare(strict_types=1);

namespace App\LoginModule\Presenters;

use Nette;
use Nette\Application\UI\Form;
use App\LoginModule\Model\MyAuthenticator;
use App\LoginModule\Model\DuplicateNameException;

final class SignUpPresenter extends \App\CoreModule\Presenters\BasePresenter
{

	private MyAuthenticator $MyAuthenticator;

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

	public function __construct(MyAuthenticator $MyAuthenticator)
	{
		$this->MyAuthenticator = $MyAuthenticator;
	}

	protected function createComponentSignUpForm(): Form
	{
		$form = new Form;
		$form->addProtection();
		$form->addEmail('email')->setRequired('Zadejte email, prosím.')->addRule($form::MAX_LENGTH, 'email je příliž dlouhý', 48)->setHtmlAttribute('placeholder','Email');
		$form->addPassword('password')->setRequired('Zadejte heslo, prosím.')->addRule($form::MIN_LENGTH, 'Heslo musí mít alespoň %d znaků', 8)->setHtmlAttribute('placeholder','heslo');
		$form->addPassword('passwordVerify')->setHtmlAttribute('placeholder','Heslo znovu')
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
			$this->MyAuthenticator->add($values->email, $values->password);
			$this->getUser()->login($values->email, $values->password);
			$this->getUser()->setExpiration('30 minutes');
			$this->redirect(':User:UserEdit:',true);
		} 
		catch (DuplicateNameException $e) 
		{
			$form->addError('Duplicitní účet');
		}		
	}
}
