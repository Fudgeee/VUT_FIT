<?php

declare(strict_types=1);

namespace App\AdminModule\Presenters;

use Nette\Application\UI\Form;
use App\AdminModule\Model\UserAdmPage;
use App\UserModule\Model\EditUser;
use App\LoginModule\Model\MyAuthenticator;
use App\LoginModule\Model\DuplicateNameException;
use Nette;


final class UserAdmCreatePresenter extends  \App\CoreModule\Presenters\LogedPresenter
{
    protected function startup(): void
	{
		parent::startup();
		$this->resorceAutorize('AdminPage');
	}
	private MyAuthenticator $MyAuthenticator;
	private UserAdmPage $admContoler;
	private EditUser $eUser;

	public function __construct(UserAdmPage $admContoler,EditUser $eUser,MyAuthenticator $MyAuthenticator)
	{
        $this->admContoler=$admContoler;
		$this->eUser=$eUser;
		$this->MyAuthenticator=$MyAuthenticator;
	}

    protected function createComponentAdmCreateProfileForm(): Form
	{
       	$form = $this->admContoler->formBase(true);
		$form->addSubmit('create', 'Přidat')->onClick[] = [$this, 'CreatePressed'];
		$form->addProtection();

		return $form;
	}
	public function CreatePressed(Form $form, \stdClass $values): void
	{
		$this->resorceAutorize('AdminPage');
		
		try 
		{
			$this->MyAuthenticator->add($values->ID,$values->password,$values->role);
		} 
		catch (DuplicateNameException $e) 
		{
			$form->addError('Uživatel exituje, zvolte prosím jiný login');
		}
		$this->eUser->saveProfileData($values->ID,$values);
		$this->redirect('UserAdmEdit:',$values->ID);
	}
}



