<?php

declare(strict_types=1);

namespace App\LibraryModule\Presenters;

use App\LibraryModule\Model\LibraryModel;
use Nette;


final class ViewLibrariesPresenter extends  \App\CoreModule\Presenters\BasePresenter
{
	private LibraryModel $LibraryModel;

	public function __construct(LibraryModel $LibraryModel)
	{
        $this->LibraryModel=$LibraryModel;
	}

	public function renderDefault(): void
	{
        $this->template->knihovny= $this->LibraryModel->getLibraries();
	}
}
