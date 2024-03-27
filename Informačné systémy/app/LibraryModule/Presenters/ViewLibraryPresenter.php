<?php

declare(strict_types=1);

namespace App\LibraryModule\Presenters;

use App\LibraryModule\Model\LibraryModel;
use Nette;


final class ViewLibraryPresenter extends  \App\CoreModule\Presenters\BasePresenter
{
	private LibraryModel $LibraryModel;

	public function __construct(LibraryModel $LibraryModel)
	{
        $this->LibraryModel=$LibraryModel;
	}

	public function renderDefault(string $libraryName): void
	{
        $this->template->knihovna= $this->LibraryModel->getLibrary($libraryName);
	}
}
