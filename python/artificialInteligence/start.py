#!/usr/bin/env python


# Load libraries
import pandas
from pandas.tools.plotting import scatter_matrix
import matplotlib.pyplot as plt
from sklearn import model_selection
from sklearn.metrics import classification_report
from sklearn.metrics import confusion_matrix
from sklearn.metrics import accuracy_score
from sklearn.linear_model import LogisticRegression
from sklearn.tree import DecisionTreeClassifier
from sklearn.neighbors import KNeighborsClassifier
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis
from sklearn.naive_bayes import GaussianNB
from sklearn.svm import SVC



# Load dataset
url = "https://archive.ics.uci.edu/ml/machine-learning-databases/iris/iris.data"
url = "file:///tmp/file.csv"
#names = ['sepal-length', 'sepal-width', 'petal-length', 'petal-width', 'class']
names = ["ANO","RESPOSTA","valor_ALUMINUM","valorizacao_ALUMINUM","percentual_ALUMINUM","valor_ANGLO","valorizacao_ANGLO","percentual_ANGLO","valor_USA_GROWTH_RATE","valor_USA_ANUAL_GROWTH","valor_USA_GDP","valor_USA_GDP_CONSTANT_PRICES","valor_USA_GROSS_NATIONAL_PRODUCT","valor_USA_GROSS_FIXED_CAPITAL_FORMATION","valor_USA_GDP_PERCAPITA","valor_USA_GDP_PERCAPITA_PPP","valor_USA_GDP_FROM_AGRICULTURE","valor_USA_GDP_FROM_CONSTRUCTION","valor_USA_GDP_FROM_MANUFACTURING","valor_USA_GDP_FROM_MINING","valor_USA_GDP_FROM_PUBLIC_ADMINISTRATION","valor_USA_GDP_FROM_SERVICES","valor_USA_GDP_FROM_TRANSPORT","valor_USA_GDP_FROM_UTILITIES","valor_CLIFF","valorizacao_CLIFF","percentual_CLIFF","valor_COAL","maximo_COAL","minimo_COAL","valor_COOPER_UK","valorizacao_COOPER_UK","percentual_COOPER_UK","valor_COOPER_US","valorizacao_COOPER_US","percentual_COOPER_US","valor_CSNA3","valorizacao_CSNA3","percentual_CSNA3","valor_DJI","valorizacao_DJI","percentual_DJI","valor_BUSINESS_CONFIDENCE","valor_MANUFACTURING_PMI","valor_NON_MANUFACTURING_PMI","valor_SERVICES_PMI","valor_INDUSTRIAL_PRODUCTION","valor_INDUSTRIAL_PRODUCTION_MOM","valor_MANUFACTURING_PRODUCTION","valor_NEW_ORDERS","valor_CHANGE_IN_INVENTORIES","valor_TOTAL_VEHICLE_SALES","valor_CAR_PRODUCTION","valor_CAR_REGISTRATIONS","valor_LEADING_ECONOMIC_INDEX","valor_MNI_BUSINESS_SENTIMENT","valor_STELL_PRODUCTION","valor_COMPETITIVENESS_INDEX","valor_COMPETITIVENESS_RANK","valor_CEMENT_PRODUCTION","valor_EASE_OF_DOING_BUSINESS","valor_ELECTRICITY_PRODUCTION","valor_CORRUPTION_INDEX","valor_CORRUPTION_RANK","valor_CORPORATE_PROFITS","valor_TOTAL_VEHICLE_SALES","valor_CAR_PRODUCTION","valor_CAR_REGISTRATIONS","valor_BRASIL_GROWTH_RATE","valor_BRASIL_ANUAL_GROWTH","valor_BRASIL_GDP","valor_BRASIL_GDP_CONSTANT_PRICES","valor_BRASIL_GROSS_NATIONAL_PRODUCT","valor_BRASIL_GROSS_FIXED_CAPITAL_FORMATION","valor_BRASIL_GDP_PERCAPITA","valor_BRASIL_GDP_PERCAPITA_PPP","valor_BRASIL_GDP_FROM_AGRICULTURE","valor_BRASIL_GDP_FROM_CONSTRUCTION","valor_BRASIL_GDP_FROM_MANUFACTURING","valor_BRASIL_GDP_FROM_MINING","valor_BRASIL_GDP_FROM_PUBLIC_ADMINISTRATION","valor_BRASIL_GDP_FROM_SERVICES","valor_BRASIL_GDP_FROM_TRANSPORT","valor_BRASIL_GDP_FROM_UTILITIES","valor_HOUSING_INDEX_LAST","valor_HOUSING_INDEX_PREVIOUS","valor_HOUSING_INDEX_HIGHEST","valor_HOUSING_INDEX_LOWEST","valor_HOUSING_OWNERSHIP_RATE_LAST","valor_HOUSING_OWNERSHIP_RATE_PREVIOUS","valor_HOUSING_OWNERSHIP_RATE_HIGHEST","valor_HOUSING_OWNERSHIP_RATE_LOWEST","valor_INDUSTRIAL_PRODUCTION_ACTUAL","valor_INDUSTRIAL_PRODUCTION_Q4_16","valor_INDUSTRIAL_PRODUCTION_Q1_17","valor_INDUSTRIAL_PRODUCTION_Q2_17","valor_INDUSTRIAL_PRODUCTION_Q3_17","valor_INDUSTRIAL_PRODUCTION_2020","valor_INTEREST_RATE_LAST","valor_INTEREST_RATE_Q4_16","valor_INTEREST_RATE_Q1_17","valor_INTEREST_RATE_Q2_17","valor_INTEREST_RATE_Q3_17","valor_INTEREST_RATE_2020","valor_CASH_RESERVE_RATIO_LAST","valor_CASH_RESERVE_RATIO_Q4_16","valor_CASH_RESERVE_RATIO_Q1_17","valor_CASH_RESERVE_RATIO_Q2_17","valor_CASH_RESERVE_RATIO_Q3_17","valor_CASH_RESERVE_RATIO_2020","valor_INTERBANK_RATE_LAST","valor_INTERBANK_RATE_Q4_16","valor_INTERBANK_RATE_Q1_17","valor_INTERBANK_RATE_Q2_17","valor_INTERBANK_RATE_Q3_17","valor_INTERBANK_RATE_2020","valor_MONEY_SUPPLY_M0_LAST","valor_MONEY_SUPPLY_M0_Q4_16","valor_MONEY_SUPPLY_M0_Q1_17","valor_MONEY_SUPPLY_M0_Q2_17","valor_MONEY_SUPPLY_M0_Q3_17","valor_MONEY_SUPPLY_M0_2020","valor_MONEY_SUPPLY_M1_LAST","valor_MONEY_SUPPLY_M1_Q4_16","valor_MONEY_SUPPLY_M1_Q1_17","valor_MONEY_SUPPLY_M1_Q2_17","valor_MONEY_SUPPLY_M1_Q3_17","valor_MONEY_SUPPLY_M1_2020","valor_MONEY_SUPPLY_M2_LAST","valor_MONEY_SUPPLY_M2_Q4_16","valor_MONEY_SUPPLY_M2_Q1_17","valor_MONEY_SUPPLY_M2_Q2_17","valor_MONEY_SUPPLY_M2_Q3_17","valor_MONEY_SUPPLY_M2_2020","valor_FOREIGN_ENCHANGE_RESERVES_LAST","valor_FOREIGN_ENCHANGE_RESERVES_Q4_16","valor_FOREIGN_ENCHANGE_RESERVES_Q1_17","valor_FOREIGN_ENCHANGE_RESERVES_Q2_17","valor_FOREIGN_ENCHANGE_RESERVES_Q3_17","valor_FOREIGN_ENCHANGE_RESERVES_2020","valor_CENTRAL_BANK_BALANCE_SHEET_LAST","valor_CENTRAL_BANK_BALANCE_SHEET_Q4_16","valor_CENTRAL_BANK_BALANCE_SHEET_Q1_17","valor_CENTRAL_BANK_BALANCE_SHEET_Q2_17","valor_CENTRAL_BANK_BALANCE_SHEET_Q3_17","valor_CENTRAL_BANK_BALANCE_SHEET_2020","valor_BANKS_BALANCE_SHEET_LAST","valor_BANKS_BALANCE_SHEET_Q4_16","valor_BANKS_BALANCE_SHEET_Q1_17","valor_BANKS_BALANCE_SHEET_Q2_17","valor_BANKS_BALANCE_SHEET_Q3_17","valor_BANKS_BALANCE_SHEET_2020","valor_LOANS_TO_PRIVATE_SECTOR_LAST","valor_LOANS_TO_PRIVATE_SECTOR_Q4_16","valor_LOANS_TO_PRIVATE_SECTOR_Q1_17","valor_LOANS_TO_PRIVATE_SECTOR_Q2_17","valor_LOANS_TO_PRIVATE_SECTOR_Q3_17","valor_LOANS_TO_PRIVATE_SECTOR_2020","valor_DEPOSIT_INTEREST_RATE_LAST","valor_DEPOSIT_INTEREST_RATE_Q4_16","valor_DEPOSIT_INTEREST_RATE_Q1_17","valor_DEPOSIT_INTEREST_RATE_Q2_17","valor_DEPOSIT_INTEREST_RATE_Q3_17","valor_DEPOSIT_INTEREST_RATE_2020","valor_LOAN_GROWTH_LAST","valor_LOAN_GROWTH_Q4_16","valor_LOAN_GROWTH_Q1_17","valor_LOAN_GROWTH_Q2_17","valor_LOAN_GROWTH_Q3_17","valor_LOAN_GROWTH_2020","valor_LOANS_TO_BANKS_LAST","valor_LOANS_TO_BANKS_Q4_16","valor_LOANS_TO_BANKS_Q1_17","valor_LOANS_TO_BANKS_Q2_17","valor_LOANS_TO_BANKS_Q3_17","valor_LOANS_TO_BANKS_2020","valor_FGV_CONSUMER_CONFIDENCE","projecao_FGV_CONSUMER_CONFIDENCE","previo_FGV_CONSUMER_CONFIDENCE","valor_IRON_SINA_CN","maximo_IRON_SINA_CN","minimo_IRON_SINA_CN","media_SINA_CN","valor_GGBR4","valorizacao_GGBR4","percentual_GGBR4","valor_GOAU4","valorizacao_GOAU4","percentual_GOAU4","valor_GOLL4","valorizacao_GOLL4","percentual_GOLL4","valor_IBOVESPA","valorizacao_IBOVESPA","percentual_IBOVESPA","valor_IRON_FE62","valorizacao_IRON_FE62","percentual_IRON_FE62","valor_IRON_ORE_PELLETS","maximo_IRON_ORE_PELLETS","minimo_IRON_ORE_PELLETS","valor_MANGANESE","maximo_MANGANESE","minimo_MANGANESE","valor_NICKEL","valorizacao_NICKEL","percentual_NICKEL","valor_PETR4","valorizacao_PETR4","percentual_PETR4","valor_RIO_TINTO","valorizacao_RIO_TINTO","percentual_RIO_TINTO","valor_SP500","valorizacao_SP500","percentual_SP500","valor_USIM5","valorizacao_USIM5","percentual_USIM5","climadaCHINA","negociacaoentreEUAeBRASIL","aberturadoEURO","prisaodolula","justicacondenasamarco","descobertadejazidademinerionachina","criseemalgumpais/EURO","problema/beneficiocomalgumaempresaconcorrente(naturezaexterna)","novoprocessojudicial"]


dataset = pandas.read_csv(url, names=names)

# shape
print(dataset.shape)


# head
print(dataset.head(20))


# descriptions
print(dataset.describe())



# class distribution
#print(dataset.groupby('class').size())
print(dataset.groupby('ANO').size())



# box and whisker plots
#dataset.plot(kind='box', subplots=True, layout=(9,106), sharex=False,sharey=False)
#plt.show()



# histograms
dataset.hist()
#plt.show()


# scatter plot matrix
scatter_matrix(dataset)
#plt.show()



# Split-out validation dataset
array = dataset.values
X = array[:,0:4]
Y = array[:,4]
validation_size = 0.20
seed = 7
X_train, X_validation, Y_train, Y_validation = model_selection.train_test_split(X, Y, test_size=validation_size,random_state=seed)


# Test options and evaluation metric
seed = 7
scoring = 'accuracy'

print(scoring)



# Spot Check Algorithms
models = []
models.append(('LR', LogisticRegression()))
models.append(('LDA', LinearDiscriminantAnalysis()))
models.append(('KNN', KNeighborsClassifier()))
models.append(('CART', DecisionTreeClassifier()))
models.append(('NB', GaussianNB()))
models.append(('SVM', SVC()))
# evaluate each model in turn
results = []
names = []
for name, model in models:
	kfold = model_selection.KFold(n_splits=10, random_state=seed)
	cv_results = model_selection.cross_val_score(model, X_train, Y_train,cv=kfold, scoring=scoring)
	results.append(cv_results)
	names.append(name)
	msg = "%s: %f (%f)" % (name, cv_results.mean(), cv_results.std())
	print(msg)



# Compare Algorithms
fig = plt.figure()
fig.suptitle('Algorithm Comparison')
ax = fig.add_subplot(111)
plt.boxplot(results)
ax.set_xticklabels(names)
#plt.show()


# Make predictions on validation dataset
knn = KNeighborsClassifier()
knn.fit(X_train, Y_train)
predictions = knn.predict(X_validation)
print(accuracy_score(Y_validation, predictions))
print(confusion_matrix(Y_validation, predictions))
print(classification_report(Y_validation, predictions))
