/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2020 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::multiComponentMixture

Description
    Foam::multiComponentMixture

SourceFiles
    multiComponentMixture.C

\*---------------------------------------------------------------------------*/

#ifndef multiComponentMixture_H
#define multiComponentMixture_H

#include "basicSpecieMixture.H"
#include "HashPtrTable.H"
#include "specieElement.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                    Class multiComponentMixture Declaration
\*---------------------------------------------------------------------------*/

template<class ThermoType>
class multiComponentMixture
:
    public basicSpecieMixture
{

public:

    //- The type of thermodynamics this mixture is instantiated for
    typedef ThermoType thermoType;


private:

    // Private Data

        //- List of specie thermo
        PtrList<ThermoType> specieThermos_;

        typedef HashTable<List<specieElement>> speciesCompositionTable;

        //- Table of species composition
        speciesCompositionTable speciesComposition_;


    // Private Member Functions

        //- Read the species data from the given dictionary and return
        PtrList<ThermoType> readSpeciesData(const dictionary& thermoDict) const;

        //- Read the species composition from the given dictionary and return
        speciesCompositionTable readSpeciesComposition
        (
            const dictionary& thermoDict,
            const speciesTable& speciesTable_
        ) const;


public:

    // Constructors

        //- Construct from dictionary, mesh and phase name
        multiComponentMixture(const dictionary&, const fvMesh&, const word&);

        //- Disallow default bitwise copy construction
        multiComponentMixture
        (
            const multiComponentMixture<ThermoType>&
        ) = delete;


    //- Destructor
    virtual ~multiComponentMixture()
    {}


    // Member Functions

        //- Return the raw specie thermodynamic data
        const PtrList<ThermoType>& specieThermos() const
        {
            return specieThermos_;
        }

        //- Return the table of species composition
        const speciesCompositionTable& specieComposition() const
        {
            return speciesComposition_;
        }

        //- Read dictionary
        void read(const dictionary&);

        //- Return thermo based on index
        inline const ThermoType& specieThermo(const label speciei) const
        {
            return specieThermos_[speciei];
        }
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
    #include "multiComponentMixture.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
