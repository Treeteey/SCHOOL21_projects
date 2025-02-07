from sqlalchemy import create_engine

# Replace credentials with your values
engine = create_engine("postgresql+psycopg2://postgres:password@localhost:5432/spaceships_db")
try:
    with engine.connect() as conn:
        print("Connected to the database successfully!")
except Exception as e:
    print(f"Connection failed: {e}")