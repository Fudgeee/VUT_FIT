<?php

declare(strict_types=1);

namespace App\BorrowingModule\Presenters;

use Nette\Utils\DateTime;
use App\LoginModule\Model\DuplicateNameException;
use Nette;
use Nette\Application\UI\Form;
use App\BorrowingModule\Model\BorrowingModel;

final class UserBorrowsPresenter extends \App\CoreModule\Presenters\LogedPresenter
{

    private BorrowingModel $BM;

	public function __construct(BorrowingModel $BM)
	{
        $this->BM=$BM;
	}

	public function renderDefault(): void
	{
		$this->resorceAutorize('UserBorrow');
		$this->template->vypujcky=$this->BM->getBorrows($this->user->getIdentity()->getId());			
	}

}
