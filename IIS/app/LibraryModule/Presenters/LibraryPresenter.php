<?php

declare(strict_types=1);

namespace App\LibraryModule\Presenters;

use App\LibraryModule\Model\LibraryModel;
use Nette;


final class LibraryPresenter extends  \App\CoreModule\Presenters\LogedPresenter
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
		}

	}

}
