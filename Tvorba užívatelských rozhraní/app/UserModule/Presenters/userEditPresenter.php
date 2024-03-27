<?php
/**
 * @brief editUser presenter
 *
 * @author Adrián Matušík (xmatus35)
 */
declare(strict_types=1);

namespace App\UserModule\Presenters;
use App\UserModule\Model\EditUser;
use App\LoginModule\Model\DuplicateNameException;

use Nette;
use Nette\Application\UI\Form;

final class UserEditPresenter extends  \App\CoreModule\Presenters\LogedPresenter
{

    private EditUser $eUser;
	private $ProfData;
	public function __construct(EditUser $eUser)
	{
        $this->eUser=$eUser;
	}

	public function renderDefault($redrawNav=false): void
	{
		$this->ProfData=$this->eUser->getProfileData($this->getUser()->getIdentity()->getId());
		if($redrawNav)
			$this->redrawControl('nav');
	}

	protected function createComponentEditProfileForm(): Form
	{
		$form = new Form;
		$form->addEmail('email', 'E-mail')->addRule($form::MAX_LENGTH, 'Email je příliž dlouhý', 64);
		$form->addText('name', 'Jméno')->addRule($form::MAX_LENGTH, 'jméno je příliž dlouhé', 48);
		$form->addText('surname', 'Přijmení')->addRule($form::MAX_LENGTH, 'přijmení je příliž dlouhé', 48);
		$form->addText('phone', 'Telefon')->addRule($form::MAX_LENGTH, 'telefon je příliž dlouhý', 16);
		$form->addText('town', 'Město')->addRule($form::MAX_LENGTH, 'mesto je příliž dlouhé', 64);
		$form->addText('street', 'Ulice')->addRule($form::MAX_LENGTH, 'ulice je příliž dlouhý', 64);
		$form->addText('pc', 'PSČ')->addRule($form::MAX_LENGTH, 'psc je příliž dlouhý', 8);

		$form->addPassword('password', 'Změna hesla')->addRule($form::MIN_LENGTH, 'Heslo musí mít alespoň %d znaků', 8);
		$form->addPassword('passwordVerify', 'Heslo znovu')
			->addRule($form::EQUAL, 'Hesla se neshodují', $form['password']);
		$form->addSubmit('send', 'Uložit')->setHtmlAttribute('class','ajax');

		$form->onSuccess[] = [$this, 'editFormSucceeded'];
		$form->setDefaults($this->ProfData);
		$form->addProtection();
		
		return $form;
	}
	public function editFormSucceeded(Form $form, \stdClass $values): void
	{
		try 
		{
			$this->eUser->saveProfileData($this->getUser()->getIdentity()->getId(),$values);

		} catch (DuplicateNameException $e) 
		{
			$form->addError('Pod tímto emailem je registrovaný jiný uživatel, prosím zvolte si jiný');
		}	
	}
}
