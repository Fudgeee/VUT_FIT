<?php

declare(strict_types=1);

namespace App\BookModule\Presenters;

use Nette;
use Nette\Application\UI\Form;
use App\BookModule\Model\BookFinder;

final class VyhledaniPresenter extends \App\CoreModule\Presenters\BasePresenter
{
    
    private BookFinder $search;

	public function __construct(BookFinder $search)
	{
        $this->search=$search;
	}

    public function renderDefault( string $text="", string $method="nazev" ): void
	{
       if($text!="")
       {
            $this->template->knihy= $this->search->searchBooks($text,$method);
       }
       else
       {
            $this->template->knihy= $this->search->listAll();
       }
	}

    protected function createComponentVyhledaniForm(): Form
    {
        $form = new Form; // means Nette\Application\UI\Form

        $form->addText('vyraz', 'Hledany výraz:')->setRequired('Zadejte hledaný výraz, prosím.');
        $typ = [
            'nazev' => 'Název knihy',
            'zanr' => 'Žánr',
            'tag' => 'Tag'
        ];
            
        $form->addSelect('typZaznamu', 'Podle čeho hledat:', $typ)
            ->setDefaultValue('nazev');

        $form->addSubmit('submit', 'vyhledat');
        $form->onSuccess[] = [$this, 'vyhledaniFormSucceeded'];
        return $form;
    }
    public function vyhledaniFormSucceeded(\stdClass $values): void
    { 
        $this->redirect(':Book:Vyhledani:',$values->vyraz,$values->typZaznamu);
    }
}
