#include "LibChemist/BasisSetParser.hpp"
#include "TestHelpers.hpp"

using namespace LibChemist;

//A shortened g94 entry, parts of this are from aDZ others from 6-31G*
std::string g94_example=
        "! Elements                             References\n"
        "! --------                             ----------\n"
        "! Ca     : J. Koput and K.A. Peterson, J. Phys. Chem. A, 106, 9595 (2002).\n"
        "! \n"
        "\n"
        "****\n"
        "H     0 \n"
        "S   3   1.00\n"
        "     13.0100000              0.0196850        \n"
        "      1.9620000              0.1379770        \n"
        "      0.4446000              0.4781480        \n"
        "S   1   1.00\n"
        "      0.1220000              1.0000000        \n"
        "****\n"
        "C     0 \n"
        "S   8   1.00\n"
        "   6665.0000000              0.0006920        \n"
        "   1000.0000000              0.0053290        \n"
        "    228.0000000              0.0270770        \n"
        "     64.7100000              0.1017180        \n"
        "     21.0600000              0.2747400        \n"
        "      7.4950000              0.4485640        \n"
        "      2.7970000              0.2850740        \n"
        "      0.5215000              0.0152040        \n"
        "D   1   1.00\n"
        "      0.1510000              1.0000000        \n"
        "SP   1   1.00\n"
        "    0.1687144              1.0000000              1.0000000 \n"
        "****\n"
        "\n"
        "\n"
        "\n";

int main()
{
    Tester tester("Testing basis set parsing capabilities");
    std::map<size_t,std::vector<BasisShell>> g94_corr;
    g94_corr[1].push_back(
                BasisShell(ShellType::SphericalGaussian,0,1,
                    std::vector<double>({13.0100000,1.9620000,0.4446000}),
                    std::vector<double>({0.0196850,0.1379770,0.4781480})));
    g94_corr[1].push_back(
                BasisShell(ShellType::SphericalGaussian,0,1,
                    std::vector<double>({0.1220000}),
                    std::vector<double>({1.0000000})));
    g94_corr[6].push_back(
                BasisShell(ShellType::SphericalGaussian,0,1,
        std::vector<double>({6665.0000000,1000.0000000,228.0000000,
                             64.7100000,21.0600000,7.4950000,2.7970000,
                             0.5215000}),
        std::vector<double>({0.0006920,0.0053290,0.0270770,0.1017180,
                            0.2747400,0.4485640,0.2850740,0.0152040})));
    g94_corr[6].push_back(
                BasisShell(ShellType::SphericalGaussian,2,1,
                           std::vector<double>({0.1510000}),
                           std::vector<double>({1.0000000})));
    g94_corr[6].push_back(
                BasisShell(ShellType::SphericalGaussian,-1,2,
                           std::vector<double>({0.1687144}),
                           std::vector<double>({1.0000000,1.000000})));
    std::stringstream ss(g94_example);
    auto rv=parse_basis_set_file(ss,G94());
    tester.test("Gaussian94 parser",rv==g94_corr);

    return tester.results();
}
