<?php

declare(strict_types=1);

namespace App\LibraryModule\Presenters;

use App\LoginModule\Model\DuplicateNameException;
use App\LibraryModule\Model\LibraryModel;
use Nette\Application\UI\Form;
use Nette;


final class LibraryAddPresenter extends  \App\CoreModule\Presenters\LogedPresenter
{
    protected function startup(): void
	{
		parent::startup();
		if(!$this->getUser()->isInRole('admin'))
		{
			$this->error('Sem nemáte přístup.',403);
		}
	}

	private LibraryModel $LibraryModel;

	public function __construct(LibraryModel $LibraryModel)
	{
        $this->LibraryModel=$LibraryModel;
	}

	private $libaryData;

	public function renderDefault(): void
	{
		
	}
	protected function createComponentLibraryAddForm(): Form
	{
		$form = new Form;
		$form->addText('ID', 'ID')->addRule($form::MAX_LENGTH, 'Název je příliš dlouhý', 255);
		$form->addSubmit('submit', 'Vytvořit knihovnu')->onClick[] = [$this, 'AddPressed'];
		$form->addProtection();

		return $form;
	}

	public function AddPressed(Form $form, \stdClass $values): void
	{
		if(!$this->getUser()->isInRole('admin'))
			$this->error('Sem nemáte přístup.',403);
		else
		{
			try 
			{
				$this->LibraryModel->addLibrary($values->ID);
				$this->redirect('LibraryEdit:',$values->ID);

			} catch (DuplicateNameException $e) 
			{
				$form->addError('Knihovna již exituje, zvolte prosím jiný název');
			}
		}
	}
}
