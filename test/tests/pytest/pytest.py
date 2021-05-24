import configparser
import shutil
import subprocess
import os

import pandas as pd
import matplotlib.pyplot as plt

ini_path = 'test/tests/pytest/test.ini'


# leave this function alone
def get_data():
    config = configparser.ConfigParser()
    try:
        config.read(ini_path)
    except FileNotFoundError:
        print(f'Could not find ini file at {ini_path}')
        print('Exiting...')
        exit(1)
    general = config['General']
    sectional = config['Sectional State']
    moment = config['Moment State']
    gas = config['Gas State']
    state = config['State']

    arguments = []

    arguments.append(general['TestExecuatable'])
    arguments.append(general['Output'])
    arguments.append(general['PSDModel'])
    arguments.append(general['CoagulationMethod'])
    arguments.append(general['GrowthMethod'])
    arguments.append(general['NucleationMethod'])
    arguments.append(general['OxidationMethod'])
    arguments.append(general['Steps'])

    arguments.append(sectional['Section0Ini'])
    arguments.append(sectional['Section0Fin'])
    arguments.append(sectional['Section1Ini'])
    arguments.append(sectional['Section1Fin'])
    arguments.append(sectional['Section2Ini'])
    arguments.append(sectional['Section2Fin'])
    arguments.append(sectional['Section3Ini'])
    arguments.append(sectional['Section3Fin'])
    arguments.append(sectional['Section4Ini'])
    arguments.append(sectional['Section4Fin'])
    arguments.append(sectional['Section5Ini'])
    arguments.append(sectional['Section5Fin'])
    arguments.append(sectional['Section6Ini'])
    arguments.append(sectional['Section6Fin'])
    arguments.append(sectional['Section7Ini'])
    arguments.append(sectional['Section7Fin'])
    arguments.append(sectional['Section8Ini'])
    arguments.append(sectional['Section8Fin'])
    arguments.append(sectional['Section9Ini'])
    arguments.append(sectional['Section9Fin'])

    arguments.append(moment['Moment0Ini'])
    arguments.append(moment['Moment0Fin'])
    arguments.append(moment['Moment1Ini'])
    arguments.append(moment['Moment1Fin'])
    arguments.append(moment['Moment2Ini'])
    arguments.append(moment['Moment2Fin'])
    arguments.append(moment['Moment3Ini'])
    arguments.append(moment['Moment3Fin'])
    arguments.append(moment['Moment4Ini'])
    arguments.append(moment['Moment4Fin'])
    arguments.append(moment['Moment5Ini'])
    arguments.append(moment['Moment5Fin'])
    arguments.append(moment['Moment6Ini'])
    arguments.append(moment['Moment6Fin'])
    arguments.append(moment['Moment7Ini'])
    arguments.append(moment['Moment7Fin'])
    arguments.append(moment['Moment8Ini'])
    arguments.append(moment['Moment8Fin'])
    arguments.append(moment['Moment9Ini'])
    arguments.append(moment['Moment9Fin'])

    arguments.append(gas['TempIni'])
    arguments.append(gas['TempFin'])
    arguments.append(gas['PresIni'])
    arguments.append(gas['PresFin'])
    arguments.append(gas['RhoGasIni'])
    arguments.append(gas['RhoGasFin'])
    arguments.append(gas['MWGasIni'])
    arguments.append(gas['MWGasFin'])
    arguments.append(gas['MuGasIni'])
    arguments.append(gas['MuGasFin'])

    arguments.append(gas['C_C2H2Ini'])
    arguments.append(gas['C_C2H2Fin'])
    arguments.append(gas['C_O2Ini'])
    arguments.append(gas['C_O2Fin'])
    arguments.append(gas['C_HIni'])
    arguments.append(gas['C_HFin'])
    arguments.append(gas['C_H2Ini'])
    arguments.append(gas['C_H2Fin'])
    arguments.append(gas['C_OHIni'])
    arguments.append(gas['C_OHFin'])
    arguments.append(gas['C_H2OIni'])
    arguments.append(gas['C_H2OFin'])
    arguments.append(gas['C_COIni'])
    arguments.append(gas['C_COFin'])
    arguments.append(gas['C_CIni'])
    arguments.append(gas['C_CFin'])

    for i in range(6, 205, 6):
        arguments.append(gas[f'{i}Ini'])
        arguments.append(gas[f'{i}Fin'])

    arguments.append(state['CMinIni'])
    arguments.append(state['CMinFin'])

    if any([arg == '' for arg in arguments]):
        print('There is an empty argument - this will probably be a problem')

    print('[Starting test subprocess]')
    try:
        shutil.rmtree(general['Output'])
    except FileNotFoundError:
        pass
    except PermissionError:
        print(f'Unabled to clear output directory: {general["Output"]}')
        print('Exiting...')
        exit(1)
    os.mkdir(general['Output'])
    complete = subprocess.run(arguments)
    print(f'[Exited with code {complete.returncode}]')
    print()

    try:
        return pd.read_csv(general['Output'] + '/data.csv'), general['Output']
    except FileNotFoundError:
        print(f'Could not find {general["Output"] +"/data.csv"}')
        print('Exiting...')
        exit(1)


# edit this function to use the data (in the form of a pandas dataframe) how you want
# Column headers:
# section_i..., moment_i..., T, P, RhoGas, MWGas, MuGas, C_C2H2, C_O2, C_H, C_H2, C_OH, C_H2O, C_CO, C_C, PAH_frac_i..., CMin,
# soot_source_i..., PAH_source_i..., C2H2_source, O2_source, H_source, H2_source, OH_source, H2O_source, CO_source, C_source
def use_data(df, output_dir):
    print(f'From {output_dir}')
    print(df)

    plt.title('Section 0 over time')
    plt.plot(range(len(df['section_0'])), df['section_0'])
    plt.savefig(output_dir + '/fig.png')


if __name__ == '__main__':
    use_data(*get_data())
