<?php

declare(strict_types=1);

namespace App\LibraryModule\Presenters;

use App\LibraryModule\Model\LibraryModel;
use Nette\Application\UI\Form;
use Nette;


final class LibraryEditPresenter extends  \App\CoreModule\Presenters\LogedPresenter
{
    protected function startup(): void
	{
		parent::startup();
		$this->resorceAutorize('Knihovna');
	}

	private LibraryModel $LibraryModel;

	public function __construct(LibraryModel $LibraryModel)
	{
        $this->LibraryModel=$LibraryModel;
	}

	private $libaryData;

	public function renderDefault(string $libraryName): void
	{
		$row=$this->LibraryModel->getLibraryAdm($this->user,$libraryName);
		if(!$row)
		{
			$this->error('Sem nemáte přístup.',403);
		}
		else
		{
			$this->template->knihovna=$row;
			$this->libaryData=$row;
		}

	}
	protected function createComponentLibraryEditForm(): Form
	{
       	$form = $this->LibraryModel->libEditFormCreate();
		$form->addSubmit('send', 'Uložit')->onClick[] = [$this, 'SavePressed'];
		if($this->getUser()->isInRole('admin'))
			$form->addSubmit('delete', 'Smazat knihovnu')->onClick[] = [$this, 'DeletePressed'];
		$form->setDefaults($this->libaryData);
		$form->addProtection();

		return $form;
	}

	public function SavePressed(Form $form, \stdClass $values): void
	{
		if(!$this->LibraryModel->autetizateAcess($this->user,$values->ID))
			$this->error('Sem nemáte přístup.',403);
		else
		{
			$this->LibraryModel->saveLibaryData($values->ID,$values);
		}
	}
	public function DeletePressed(Form $form, \stdClass $values): void
	{
		if(!$this->getUser()->isInRole('admin'))
			$this->error('Sem nemáte přístup.',403);
		else
		{
			$this->LibraryModel->deleteLibary( $values->ID);
			$this->redirect('LibraryDashBoard:');
		}
	}

}
