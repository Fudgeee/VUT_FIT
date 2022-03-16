<?php
namespace App\AdminModule\Model;

use Nette;
use App\LoginModule\Model\MyAuthenticator;
use App\UserModule\Model\EditUser;
use Nette\Application\UI\Form;

final class  UserAdmPage
{
	use Nette\SmartObject;
	private $database;
	private MyAuthenticator $MyAuthenticator;

	public function __construct(Nette\Database\Explorer $database,MyAuthenticator $MyAuthenticator) 
	{
		$this->database = $database;
		$this->MyAuthenticator = $MyAuthenticator;
	}

	public function getUsers()
	{
		return $this->database->table('uzivatel');
	}

	public function deleteUser(string $login)
	{
		$this->database->table('uzivatel')->where('ID', $login)->delete();;
	}

	public function formBase(bool $addAcount=false): Form
	{
		$form = new Form;
		if($addAcount)
			$form->addText('ID', 'Login:')->setRequired('Zadejte login, prosím.')->addRule($form::MAX_LENGTH, 'Uživatelské jméno je příliž dlouhé', 48);
		else
			$form->addHidden('ID');
		$typ = [
            'registered' => 'Uživatel',
            'knihovnik' => 'Knihovník',
			'distributor' => 'Distributor',
			'admin' => 'Admin',
        ];   
        $form->addSelect('role', 'Role:', $typ);
		$form->addText('meno', 'Jméno')->addRule($form::MAX_LENGTH, 'Uživatelské jméno je příliž dlouhé', 48);
		$form->addText('priezvisko', 'Přijmení')->addRule($form::MAX_LENGTH, 'Uživatelské jméno je příliž dlouhé', 48);
		$form->addEmail('email', 'E-mail')->addRule($form::MAX_LENGTH, 'Email je příliž dlouhý', 255);
		$form->addText('telefon', 'Telefon')->addRule($form::MAX_LENGTH, 'telefon je příliž dlouhý', 20);
		$form->addText('mesto', 'Město')->addRule($form::MAX_LENGTH, 'mesto je příliž dlouhý', 255);
		$form->addText('ulice', 'Ulice')->addRule($form::MAX_LENGTH, 'ulice je příliž dlouhý', 255);
		$form->addText('psc', 'PSČ')->addRule($form::MAX_LENGTH, 'psc je příliž dlouhý', 6);
		if($addAcount)	
			$form->addPassword('password', 'Heslo:')->addRule($form::MIN_LENGTH, 'Heslo musí mít alespoň %d znaků', 8)->setRequired('Zadejte heslo, prosím.');
		else
			$form->addPassword('password', 'Změna hesla:')->addRule($form::MIN_LENGTH, 'Heslo musí mít alespoň %d znaků', 8);
		$form->addPassword('passwordVerify', 'Heslo znovu:')
			->addRule($form::EQUAL, 'Hesla se neshodují', $form['password']);
		return $form;
	}
}