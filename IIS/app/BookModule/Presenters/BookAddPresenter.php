<?php

declare(strict_types=1);

namespace App\BookModule\Presenters;

use App\LoginModule\Model\DuplicateNameException;
use Nette;
use Nette\Application\UI\Form;
use App\BookModule\Model\BookFinder;

final class BookAddPresenter extends \App\CoreModule\Presenters\LogedPresenter
{
    
    private BookFinder $bookModel;

	public function __construct(BookFinder $bookModel)
	{
        $this->bookModel=$bookModel;
	}

	protected function createComponentBookAddForm(): Form
	{
		$form = new Form;
		$form->addText('ID', 'Název knihy')->addRule($form::MAX_LENGTH, 'Název je příliš dlouhý', 48);
		$form->addSubmit('submit', 'Vytvořit knihu')->onClick[] = [$this, 'AddPressed'];
		$form->addProtection();

		return $form;
	}

	public function AddPressed(Form $form, \stdClass $values): void
	{
		$this->resorceAutorize('Knihy');

		try 
		{
			$this->bookModel->addBook($values->ID);
			$this->redirect('BookEdit:',$values->ID);
		}
		catch (DuplicateNameException $e) 
		{
			$form->addError('Kniha již exituje, zvolte prosím jiný název');
		}	
	}
}
