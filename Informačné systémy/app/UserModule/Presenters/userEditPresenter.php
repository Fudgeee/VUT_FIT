<?php

declare(strict_types=1);

namespace App\UserModule\Presenters;
use App\UserModule\Model\EditUser;

use Nette;
use Nette\Application\UI\Form;

final class UserEditPresenter extends  \App\CoreModule\Presenters\LogedPresenter
{
	public function beforeRender()
	{
		$this->mySession->lock = true;
		parent::beforeRender();
	}
	
    private EditUser $eUser;
	private $ProfData;
	public function __construct(EditUser $eUser)
	{
        $this->eUser=$eUser;
	}

	public function renderDefault(): void
	{
		$this->ProfData=$this->eUser->getProfileData($this->getUser()->getIdentity()->getId());
	}

	protected function createComponentEditProfileForm(): Form
	{
		$form = new Form;
		$form->addText('meno', 'Jméno')->addRule($form::MAX_LENGTH, 'Uživatelské jméno je příliž dlouhé', 48);
		$form->addText('priezvisko', 'Přijmení')->addRule($form::MAX_LENGTH, 'Uživatelské jméno je příliž dlouhé', 48);
		$form->addEmail('email', 'E-mail')->addRule($form::MAX_LENGTH, 'Email je příliž dlouhý', 255);
		$form->addText('telefon', 'Telefon')->addRule($form::MAX_LENGTH, 'telefon je příliž dlouhý', 20);
		$form->addText('mesto', 'Město')->addRule($form::MAX_LENGTH, 'mesto je příliž dlouhý', 255);
		$form->addText('ulice', 'Ulice')->addRule($form::MAX_LENGTH, 'ulice je příliž dlouhý', 255);
		$form->addText('psc', 'PSČ')->addRule($form::MAX_LENGTH, 'psc je příliž dlouhý', 6);

		$form->addPassword('password', 'Změna hesla:')->addRule($form::MIN_LENGTH, 'Heslo musí mít alespoň %d znaků', 8);
		$form->addPassword('passwordVerify', 'Heslo znovu:')
			->addRule($form::EQUAL, 'Hesla se neshodují', $form['password']);
		$form->addSubmit('send', 'Uložit');

		$form->onSuccess[] = [$this, 'editFormSucceeded'];
		$form->setDefaults($this->ProfData);
		$form->addProtection();
		
		return $form;
	}
	public function editFormSucceeded(Form $form, \stdClass $values): void
	{
		$this->eUser->saveProfileData($this->getUser()->getIdentity()->getId(),$values);
		if($this->mySession->backlink)
			$this->restoreRequest($this->mySession->backlink);
	}
}
