from flask import Flask, request, jsonify, render_template
import pandas as pd
import numpy as np
from sklearn.linear_model import LogisticRegression
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import accuracy_score

# Load the dataset
data = pd.read_csv('data.csv')  # Ensure the path is correct
y = data['label']
x = data.drop(['label'], axis=1)

# Split the data into training and testing sets
x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.2, random_state=0)

# Scale the features using StandardScaler
scaler = StandardScaler()
x_train_scaled = scaler.fit_transform(x_train)
x_test_scaled = scaler.transform(x_test)

# Create and train the model
model = LogisticRegression()
model.fit(x_train_scaled, y_train)

# Test the model's accuracy
y_pred = model.predict(x_test_scaled)
accuracy = accuracy_score(y_test, y_pred)
print(f"Model Accuracy: {accuracy}")

app = Flask(__name__)

@app.route('/')
def home():
    return render_template('index.html')  # Ensure you have an 'index.html' in the 'templates' folder

@app.route('/predict', methods=['POST'])
def predict():
    # Get data from the frontend
    input_data = request.form.to_dict()

    # Ensure the input data is in the correct format
    try:
        print(f"Received input data: {input_data}")  # Debug log to check the form data

        # Prepare input array (convert to float)
        input_array = np.array([[float(input_data['nitrogen']), float(input_data['phosphorus']),
                                 float(input_data['potassium']), float(input_data['temperature']),
                                 float(input_data['humidity']), float(input_data['ph']),
                                 float(input_data['rainfall'])]])
        print(f"Input array: {input_array}")  # Debug log to check input array

        # Scale the input array (using the same scaler that was used for training)
        input_array_scaled = scaler.transform(input_array)

        # Make prediction
        prediction = model.predict(input_array_scaled)

        # Return the prediction as a JSON response
        return jsonify({'prediction': prediction[0]})

    except KeyError as e:
        return jsonify({'error': f'Missing input: {str(e)}'}), 400
    except ValueError as e:
        return jsonify({'error': f'Invalid input: {str(e)}'}), 400

if __name__ == '__main__':
    app.run(debug=True)
