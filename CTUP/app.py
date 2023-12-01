# Define dictionaries to store the medicine names and their prices
drogasil = {
    "Ibuprofen": 7.99,
    "Aspirin": 3.99,
    "Antacid": 4.99
}

drogariaSaoPaulo = {
    "Paracetamol": 5.99,
    "Ibuprofen": 7.99,
    "Aspirin": 3.99,
    "Antacid": 4.99
}

drogaRaia = {
    "Paracetamol": 5.99,
    "Ibuprofen": 7.99,
    "Antacid": 4.99
}

# Function to return the dictionary that has all the specified medicines
def find_pharmacy_whole_pack(medicines):
    dictionaries = {"drogasil": drogasil, "drogariaSaoPaulo": drogariaSaoPaulo, "drogaRaia": drogaRaia}
    
    for name, dictionary in dictionaries.items():
        # Check if all items in medicines are present in the dictionary
        if all(item in dictionary for item in medicines):
            # Check if the lengths of the dictionary and medicines are equal
            if len(dictionary) == len(medicines):
                return name, dictionary
    return None, None

# Function to list which dictionaries have each medicine
def list_pharmacy_for_medicines(medicines):
    dictionaries = {"drogasil": drogasil, "drogariaSaoPaulo": drogariaSaoPaulo, "drogaRaia": drogaRaia}
    result = {medicine: [name for name, dictionary in dictionaries.items() if medicine in dictionary] for medicine in medicines}
    return result

# Function to build the price for a list of medicines
def build_price(medicine_list):
    total_price = 0
    selected_dict_name, dictionary = find_pharmacy_whole_pack(medicine_list)
    
    if dictionary:
        for medicine in medicine_list:
            price = dictionary.get(medicine)
            if price is not None:
                total_price += price
            else:
                print(f"Price for {medicine} not found.")
                return None
        return total_price, selected_dict_name
    else:
        # If no matching dictionary is found, list which dictionaries have each medicine
        medicine_dicts = list_pharmacy_for_medicines(medicine_list)
        for medicine, dicts in medicine_dicts.items():
            print(f"{medicine}: {', '.join(dicts)}")
        return None, None

# Function to show the price and selected dictionary to the user
def show_price_and_dict(price, selected_dict_name):
    if price is not None:
        print("The total price for the medicines is: $", price)
        print("Selected dictionary:", selected_dict_name)
    else:
        print("Medicines not found in any dictionary.")

# Example usage
medicines = ["Paracetamol", "Ibuprofen", "Aspirin", "Antacid"]
total_price, selected_dict_name = build_price(medicines)
show_price_and_dict(total_price, selected_dict_name)
