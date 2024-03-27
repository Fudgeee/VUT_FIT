<?php

declare(strict_types=1);

namespace App\BookTransactionModule\Presenters;

use Nette\Utils\DateTime;
use App\LoginModule\Model\DuplicateNameException;
use Nette;
use Nette\Application\UI\Form;
use App\BookTransactionModule\Model\BookTransactionModel;

final class LibBooksPresenter extends \App\CoreModule\Presenters\LogedPresenter
{
	protected function startup(): void
	{
		parent::startup();
		$this->resorceAutorize('Knihovna');
	}

    private BookTransactionModel $BTM;

	public function __construct(BookTransactionModel $BTM)
	{
        $this->BTM=$BTM;
	}

	public function renderDefault(string $libName): void
	{
		if(!$this->BTM->autorize($this->user,$libName))
			$this->error("forbiden",403);
		$this->template->libName= $libName;
		$this->template->books=  $this->BTM->getBooks($libName);
	}

}
