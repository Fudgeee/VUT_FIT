<?php
/**
 * @brief rezervation presenter
 *
 * @authors Adrián Matušík (xmatus35)
 */
declare(strict_types=1);

namespace App\DashBoardModule\Presenters;
use App\DashBoardModule\Model\DashBoardModel;

use Nette;
use Nette\Application\UI\Form;
use Nette\Utils\DateTime;

final class RezervationPresenter extends  \App\CoreModule\Presenters\LogedPresenter
{

    private DashBoardModel $DBM;
	public function __construct(DashBoardModel $DBM)
	{
        $this->DBM=$DBM;
	}

	public function renderDefault(int $ID)
	{
		$this->template->reservation=$this->DBM->getRezervationBYId($ID);	

	}

	public function handleDeleteReservation(int $id): void
	{
		$this->DBM->DeleteReservation($id);
		$this->redirect(":DashBoard:DashBoard:");	
	}
	public function beforeRender()
	{

	}
	public function handleLockLock(int $id): void
	{
		$this->DBM->LockLock($id);
		$this->redrawControl('lock');
	}
	public function handleUnlockLock(int $id): void
	{
		$this->DBM->UnlockLock($id);
		$this->redrawControl('lock');
	}
}