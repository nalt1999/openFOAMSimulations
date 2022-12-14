Info<< "Reading financial properties\n" << endl;

IOdictionary financialProperties
(
    IOobject
    (
        "financialProperties",
        runTime.constant(),
        mesh,
        IOobject::MUST_READ_IF_MODIFIED,
        IOobject::NO_WRITE
    )
);

dimensionedScalar strike
(
    "strike",
    dimLength,
    financialProperties
);

dimensionedScalar r
(
    "r",
    dimless/dimTime,
    financialProperties
);

dimensionedScalar sigma
(
    "sigma",
    dimensionSet(0, 0, -0.5, 0, 0),
    financialProperties
);

dimensionedScalar sigmaSqr = sqr(sigma);


Info<< nl << "Reading field V" << endl;

volScalarField V
(
    IOobject
    (
        "V",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);


surfaceVectorField Pf
(
    IOobject
    (
        "Pf",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE
    ),
    mesh.Cf()
);


volVectorField P
(
    IOobject
    (
        "P",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE
    ),
    mesh.C()
);

V == max
(
    P.component(Foam::vector::X) - strike,
    dimensionedScalar(V.dimensions(), Zero)
);

volScalarField delta
(
    IOobject
    (
        "delta",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    fvc::grad(V)().component(Foam::vector::X)
);
