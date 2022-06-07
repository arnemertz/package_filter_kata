# Package filter

Given a list of filter criteria, select packages from a list that satisfy all filters.
As output, print the total number of items, total number of packages, total weight.

Example input:
```
filters: {
    minPackageWeight: "2kg",
    maxPackageWeight: "15kg",
    minItemWeight: "200g",
    maxItemWeight: "5kg",
    minItemCount: 2,
    maxItemCount: 50,
    minPackageCount: 1,
    maxPackageCount: 50
},
packages: [
    {itemName: "screwDriver", itemWeight: "400g", itemCount: 5, packageCount: 12},
    {itemName: "powerDrill", itemWeight: "2500g", packageCount: 5},
    {itemName: "screw", itemCount: 500, packageCount: 10, packageWeight: "500g"},
    {itemID: "DA456-32F", packageWeight: "4000g", itemWeight: "800g"},
    {itemWeight: "800g", itemCount: 6, packageWeight: "5kg", packageCount: 2, itemID: "FIA-77-g64x"},
    {itemCount: 20, itemName: "gummy bears", packageCount: 50},
    {itemCount: 10, itemWeight: "2300g", itemName: "powerDrill", powerUse="1400W"}
]
```

Formats, constraints and rules:
- counts are always plain integral numbers
- weights are quoted and either in g or kg
- itemCount is per package
- not every filter needs to be present, i.e. there may be no minimum or maximum
- if no item count is given assume an itemCount of package weight divided by item weight if both are given, else 1
- if no package count is given, assume a package count of 1
- if a package weight is missing, assume the package weight being the item weight times the item count
- if the item weight is missing, assume the item weight being the package weight divided by the item count, and rounded down to full grams
- there may be invalid packages; they never satisfy the filters
- package attributes can be listed in any order

In the above example, the following packages do not satisfy the filter criteria:
- the first powerDrill (implicit itemCount=1)
- screw (itemCount=500)
- gummy bears (invalid due to missing weights)
- the second powerDrill (implicit packageWeight=23kg)

The output for above example would be: `totalItemCount: 73, totalPackageCount: 15, totalWeight: "38000g"`
(12 packages á 5 screw drivers, 1 package with a DA456-32F, 2 packages á 6 "FIA-77g64x")
