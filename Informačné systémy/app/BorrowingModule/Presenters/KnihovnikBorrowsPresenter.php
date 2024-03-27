<?php

declare(strict_types=1);

namespace App\BorrowingModule\Presenters;

use Nette\Utils\DateTime;
use App\LoginModule\Model\DuplicateNameException;
use Nette;
use Nette\Application\UI\Form;
use App\BorrowingModule\Model\BorrowingModel;

final class KnihovnikBorrowsPresenter extends \App\CoreModule\Presenters\LogedPresenter
{

    private BorrowingModel $BM;

	public function __construct(BorrowingModel $BM)
	{
        $this->BM=$BM;
	}

	public function renderDefault(string $libID): void
	{
		$this->resorceAutorize('KnihovnikBorrow');
		if(!$this->BM->autorizeLib($this->user,$libID))
			$this->error('Forbiden',403);
		$this->template->vypujcky=$this->BM->getBorrowsFromLib($libID);
		$this->template->libName=$libID;
			
	}

}
