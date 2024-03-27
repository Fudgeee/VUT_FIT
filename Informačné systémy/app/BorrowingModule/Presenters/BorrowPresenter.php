<?php

declare(strict_types=1);

namespace App\BorrowingModule\Presenters;

use Nette\Utils\DateTime;
use App\LoginModule\Model\DuplicateNameException;
use Nette;
use Nette\Application\UI\Form;
use App\BorrowingModule\Model\BorrowingModel;

final class BorrowPresenter extends \App\CoreModule\Presenters\LogedPresenter
{

    private BorrowingModel $BM;

	public function __construct(BorrowingModel $BM)
	{
        $this->BM=$BM;
	}

	public function renderDefault(int $id): void
	{
		if(!$this->BM->accesBorrow($this->user,$id))
			$this->error('Forbiden',403);

		$var=$this->BM->getBorrow($id);
		$this->template->vypujcka=$var;

		if($var->datum_vydano)
		{
			$this->template->vratitDo=$var->datum_vydano->modifyClone('+'.(($var->prodlouzeni+1)*14).' day');

			if($var->datum_vraceno)
				$now = $var->datum_vraceno;
			else
				$now = new DateTime();

			$this->template->pocetDni=$now->diff($this->template->vratitDo)->days;
			if($now>$this->template->vratitDo)
			{
				$this->template->pokuta=$this->template->pocetDni*2;
				$this->template->nevracenoVterminu=true;
			}
			else
				$this->template->nevracenoVterminu=false;
		}				
	}

	public function handleVratit(int $id): void
	{
		$this->resorceAutorize('KnihovnikBorrow');
		if(!$this->BM->accesBorrow($this->user,$id))
			$this->error('Forbiden',403);

		$this->BM->vratitBorrow($id);
	}

	public function handleSmazat(int $id): void
	{
		$this->resorceAutorize('UserBorrow');
		if(!$this->BM->accesBorrow($this->user,$id))
			$this->error('Forbiden',403);

		$this->BM->smazatBorrow($id);
		$this->redirect(':Borrowing:UserBorrows:');
	}
	
	public function handleVydat(int $id): void
	{
		$this->resorceAutorize('KnihovnikBorrow');
		if(!$this->BM->accesBorrow($this->user,$id))
			$this->error('Forbiden',403);
			
		$this->resorceAutorize('KnihovnikBorrow');
		$this->BM->vydatBorrow($id);
	}

	public function handleVratitVyradit(int $id): void
	{
		$this->resorceAutorize('KnihovnikBorrow');
		if(!$this->BM->accesBorrow($this->user,$id))
			$this->error('Forbiden',403);

		$this->resorceAutorize('KnihovnikBorrow');
		$this->BM->vratitVyraditBorrow($id);
	}

	public function handleZamitnout(int $id): void
	{
		$this->resorceAutorize('KnihovnikBorrow');
		if(!$this->BM->accesBorrow($this->user,$id))
			$this->error('Forbiden',403);

		$this->resorceAutorize('KnihovnikBorrow');
		$this->BM->zamitnoutBorrow($id);
	}

	public function handleProdlouzit(int $id): void
	{
		$this->resorceAutorize('UserBorrow');
		if(!$this->BM->accesBorrow($this->user,$id))
			$this->error('Forbiden',403);

		if(!$this->BM->prodlouzitBorrow($id))
			$this->flashMessage('Nelze prodloužit více jak 2x');
	}
}
