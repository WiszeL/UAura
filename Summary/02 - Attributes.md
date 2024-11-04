# 1. Introduction
## 1.1 Pre Intro
While Ability System Component needs to be explicitly registered to know the owner and avatar, 
Attribute Set doesn't need to as long as it is constructed on the same place as Ability System Component.

We can have multiple Attribute Sets to separated a categorized attributes, but it is not recommended by me. It is acceptable to have multiple
category in one attribute set.

Note: Categorized attributes are such like Primary Attributes, Secondary Attributes, etc.

## 1.2 Intro
Attributes are numerical quantities associated with a given entity. All attributes are float. 
So, if you want to save something but it is not just a numerical floats, then it shouldn't be set as attribute (like inventory item, etc).

They are exists within structure `FGameplayAttributeData` and stored on Attribute Set. We can know when an attribute is 
changed and respond to it that we like. `FGameplayAttributeData` stored 2 variables, those are `BaseValue` and `CurrentValue`.
`BaseValue` is NOT the max value, max value is actually a separated attribute!

We can directly changes the value of the attribute by the code, but it is NOT recommended. The recommended way is changing 
it with `GameplayEffect` since it has built-in "Prediction" feature.