<?php

declare(strict_types=1);

namespace App\LibraryModule\Presenters;

use App\LibraryModule\Model\LibraryModel;
use Nette;


final class LibraryDashBoardPresenter extends  \App\CoreModule\Presenters\LogedPresenter
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


	public function renderDefault(): void
	{
		$this->template->knihovny=$this->LibraryModel->getLibrariesAdm($this->user,$this->getUser()->getIdentity()->getId());
	}

}
