<?php

declare(strict_types=1);

namespace App\AdminModule\Presenters;

use Nette\Application\UI\Form;
use App\AdminModule\Model\UserAdmPage;
use App\UserModule\Model\EditUser;
use Nette;


final class UserAdmEditPresenter extends  \App\CoreModule\Presenters\LogedPresenter
{
    protected function startup(): void
	{
		parent::startup();
		$this->resorceAutorize('AdminPage');
	}

	private UserAdmPage $admContoler;
	private EditUser $eUser;

	private $ProfData;

	public function __construct(UserAdmPage $admContoler,EditUser $eUser)
	{
        $this->admContoler=$admContoler;
		$this->eUser=$eUser;
	}

	public function renderDefault(string $user): void
	{
		$this->template->name=$user;
		$this->ProfData=$this->eUser->getProfileData($user);
		if(!$this->ProfData)
		{
			$this->error('Uživatel neexistuje.');
		}
	}

    protected function createComponentAdmEditProfileForm(): Form
	{
       	$form = $this->admContoler->formBase();
		$form->addSubmit('send', 'Uložit')->onClick[] = [$this, 'SavePressed'];
		$form->addSubmit('delete', 'Smazat uživatele')->onClick[] = [$this, 'DeletePressed'];
		$form->setDefaults($this->ProfData);
		$form->addProtection();

		return $form;
	}

	public function SavePressed(Form $form, \stdClass $values): void
	{
		$this->resorceAutorize('AdminPage');
		
		$this->eUser->saveProfileData($values->ID,$values);
	}
	public function DeletePressed(Form $form, \stdClass $values): void
	{
		$this->resorceAutorize('AdminPage');

		$this->admContoler->deleteUser($values->ID);
		$this->redirect('UsersAdmin:');
	}

}



