<?php

declare(strict_types=1);

namespace App\LibraryModule\Presenters;

use App\LoginModule\Model\DuplicateNameException;
use App\LibraryModule\Model\LibraryModel;
use Nette\Application\UI\Form;
use Nette;


final class LibraryAddKnihovnikPresenter extends  \App\CoreModule\Presenters\LogedPresenter
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

	private $libraryData;
	private string $libraryName;
	public function renderDefault(string $libraryName): void
	{
		$this->libraryName=$libraryName;
		$this->libraryData=$this->LibraryModel->getLibrary($libraryName);
		$this->template->knihovniks=$this->LibraryModel->getKnihovniksInLib($libraryName);
		$this->template->libName=$libraryName;
	}

	protected function createComponentAddKnihovnikForm(): Form
	{
		$form = new Form;
		$form->addHidden('ID')->setDefaultValue($this->libraryData);

		$knihovniks= $this->LibraryModel->getKnihovnik()->fetchPairs('ID');   
		foreach ($knihovniks as $knihovnik) 
		{
			$selectItems[$knihovnik->ID]=$knihovnik->meno." ".$knihovnik->priezvisko." (".$knihovnik->ID.")";	
		}

        $form->addSelect('ID_uzivatel', 'Knihovník:', $selectItems);

		$form->addSubmit('submit', 'Přidat')->onClick[] = [$this, 'AddPressed'];
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
				$this->LibraryModel->addKnihovnik($values->ID,$values->ID_uzivatel);
			} 
			catch (DuplicateNameException $e) 
			{
				$form->addError('tento knihovník již zpravuje tuto knihovnu');
			}
		}
	}

	public function handleDeleteKnihovnik(string $libraryName,string $knihovnikId): void
	{
		if(!$this->getUser()->isInRole('admin'))
		{
			$this->error('Sem nemáte přístup.',403);
		}
		$this->libraryData=$this->LibraryModel->deleteKnihovnik($libraryName,$knihovnikId);
	}
}
