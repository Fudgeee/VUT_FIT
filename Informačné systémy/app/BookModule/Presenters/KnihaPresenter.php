<?php

declare(strict_types=1);

namespace App\BookModule\Presenters;
use App\BookModule\Model\BookFinder;
use App\BorrowingModule\Model\BorrowingModel;
use Nette;
use App\LoginModule\Model\DuplicateNameException;

final class KnihaPresenter extends \App\CoreModule\Presenters\BasePresenter
{
    
	private BookFinder $bookModel;
	private BorrowingModel $BorrowingModel;
	
	public function __construct(BookFinder $bookModel,BorrowingModel $BorrowingModel)
	{
        $this->bookModel=$bookModel;
		$this->BorrowingModel=$BorrowingModel;
	}

	public function renderShow(string $id): void
	{
		$kniha = $this->bookModel->getBook($id);
		
		if (!$kniha) {
			$this->error('Kniha s není dostupná nebo byla smazána.');
		}
		$this->template->kniha = $kniha;
		$this->template->autori= $this->bookModel->getAutors($id);
		if(!$this->template->autori->count('*'))
			$this->template->autori=null;
		$this->template->voteCount=$this->bookModel->getVoteCount($id);

		$this->template->borrows=$this->bookModel->getBorrows($id);
		if($this->getUser()->getIdentity())
			$this->template->userID=$this->getUser()->getIdentity()->getId();
		else
			$this->template->userID=null;
	}

	public function handleVote(string $bookName): void
	{
		if (!$this->getUser()->isLoggedIn()) 
			$this->error('Operace zamítnuta',403);
		else
		{
			try 
			{
				$this->bookModel->voteBook($bookName,$this->user->getIdentity()->getId());
			}
			catch (DuplicateNameException $e) 
			{
				$this->flashMessage('Již jste hlasoval.');
			}	
		}
	}

	public function handleZapujcit(string $bookName,string $libaryName,string $username): void
	{
		$this->bookModel->zarezervovat($libaryName,$bookName,$username);
		$this->BorrowingModel->queueUpdate( $bookName,$libaryName);
		$this->redirect(':Borrowing:UserBorrows:');
	}

	public function handleRedirectToLogin(): void
	{
		$this->flashMessage('Pro rezervaci knihy je potřeba se přihlásit.');
		$this->redirect(':Login:SignIn:');
	}

}
