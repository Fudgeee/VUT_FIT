<?php

declare(strict_types=1);

namespace App\BookModule\Presenters;

use Nette\Utils\DateTime;
use App\LoginModule\Model\DuplicateNameException;
use Nette;
use Nette\Application\UI\Form;
use App\BookModule\Model\BookFinder;

final class BookEditPresenter extends \App\CoreModule\Presenters\LogedPresenter
{
    
    private BookFinder $bookModel;
	private $bookData;
	public function __construct(BookFinder $bookModel)
	{
        $this->bookModel=$bookModel;
	}

	protected function createComponentBookEditForm(): Form
	{
		$form = new Form;
		$form->addHidden('ID');
		$form->addTextArea('popis', 'Popis')->addRule($form::MAX_LENGTH, 'Popis je příliš dlouhý', 2048);
		$form->addText('vydavatelstvo', 'Vydavatelství')->addRule($form::MAX_LENGTH, 'Vydavatelství je příliš dlouhé', 255);
		$form->addText('zanry', 'Žánry')->addRule($form::MAX_LENGTH, 'žánry jsou příliš dlouhé', 255);
		$form->addText('tagy', 'Tagy')->addRule($form::MAX_LENGTH, 'tagy jsou příliš dlouhé', 255);
		$form->setDefaults($this->bookData);

		if(isset($this->bookData->datumVydani))
			$form->addText('datumVydani', 'Datum vydáni')->setHtmlType('date')->setDefaultValue( DateTime::from($this->bookData->datumVydani)->format('Y-m-d'));
		else
			$form->addText('datumVydani', 'Datum vydáni')->setHtmlType('date');

		$form->addSubmit('submit', 'Edtitovat knihu')->onClick[] = [$this, 'EditPressed'];
		if($this->getUser()->isInRole('admin'))
			$form->addSubmit('delete', 'Smazat knihu')->onClick[] = [$this, 'DeletePressed'];
		$form->addProtection();

		return $form;
	}

	protected function createComponentAutorCreateForm(): Form
	{
		$form = new Form;
		$form->addHidden('ID')->setDefaultValue($this->bookData);
		$form->addText('meno', 'Jméno')->addRule($form::MAX_LENGTH, 'meno je příliš dlouhé', 48);
		$form->addText('priezvisko', 'Přijmení')->addRule($form::MAX_LENGTH, 'priezvisko jsou příliš dlouhé', 48);
		$form->addSubmit('submit', 'Přidat autora')->onClick[] = [$this, 'AddAutor'];
		$form->addProtection();

		return $form;
	}

	public function AddAutor(Form $form, \stdClass $values): void
	{
		$this->resorceAutorize('Knihy');
		$this->bookModel->addAutor($values->ID,$values);
		$this->redirect('this');
	}

	public function handleDeleteAutor(string $bookName,int $discriminant): void
	{
		$this->resorceAutorize('Knihy');
		$this->bookModel->deleteAutor($bookName,$discriminant);
	}

	public function renderDefault(string $bookName): void
	{
		$this->bookData=$this->bookModel->getBook($bookName);
		$this->template->bookData=$this->bookData;
		if(!$this->bookData)
			$this->error('Kniha neexistuje',403);
		$this->template->autori= $this->bookModel->getAutors($bookName);
	}

	public function EditPressed(Form $form, \stdClass $values): void
	{
		$this->resorceAutorize('Knihy');

		try 
		{
			$this->bookModel->editBook($values->ID,$values);
		}
		catch (DuplicateNameException $e) 
		{
			$form->addError('Kniha již exituje, zvolte prosím jiný název');
		}	
	}

	public function DeletePressed(Form $form, \stdClass $values): void
	{
		if(!$this->getUser()->isInRole('admin'))
			$this->error('Sem nemáte přístup.',403);
		else
		{
			$this->bookModel->deleteBook( $values->ID);
			$this->redirect('Vyhledani:');
		}
	}
}
