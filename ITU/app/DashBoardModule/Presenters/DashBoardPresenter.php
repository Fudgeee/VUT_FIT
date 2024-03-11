<?php
/**
 * @brief dashboard presenter
 *
 * @authors Adrián Matušík (xmatus35)
 */
declare(strict_types=1);

namespace App\DashBoardModule\Presenters;
use App\DashBoardModule\Model\DashBoardModel;

use Nette;
use Nette\Application\UI\Form;
use Nette\Utils\DateTime;

final class DashBoardPresenter extends  \App\CoreModule\Presenters\LogedPresenter
{

    private DashBoardModel $DBM;
	public function __construct(DashBoardModel $DBM)
	{
        $this->DBM=$DBM;
	}

	public function renderDefault($redrawNav=false)
	{
		if($redrawNav)
			$this->redrawControl('nav');

		$this->template->reservations=$this->DBM->getRezervation($this->getUser()->getIdentity()->getId());	
	}
	public function handleDeleteReservation1(int $id): void
	{
		$this->DBM->DeleteReservation1($id);
	}
}