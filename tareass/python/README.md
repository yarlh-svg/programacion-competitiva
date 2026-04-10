# Dijkstra Perú — Ruta más corta entre departamentos

Visualización interactiva del algoritmo de Dijkstra, BFS y DFS sobre el mapa real del Perú usando geolocalización (Haversine).

---

## Requisitos

- Python 3.8 o superior
- pip disponible
- librerias: streamlit,folium,streamlit-folium,pandas

---

Instalación de librerías

Se ejecuta el siguiente comando en la terminal (PowerShell o CMD):

```bash
python -m pip install streamlit folium streamlit-folium pandas
```

| Librería | Uso |
|---|---|
| `streamlit` | Interfaz web de la aplicación |
| `folium` | Mapa interactivo |
| `streamlit-folium` | Integra Folium dentro de Streamlit |
| `pandas` | Tabla de recorrido del algoritmo |

---

## Ejecución

```bash
python -m streamlit run dijkstra_peru.py
```

La aplicación se abrirá automáticamente en el navegador en:
```
http://localhost:....
```

---

## Cómo usar la app

1. En el panel izquierdo, se selecciona el **departamento origen**
2. Se selecciona el **departamento destino**
3. Se elige el **algoritmo** (Dijkstra, BFS o DFS)
4. Se presiona **"Encontrar Ruta Óptima"**

---

## Advertencia en terminal (normal)

Al ejecutar se verá este mensaje repetido — **no es un error**, solo un aviso de Streamlit:

```
Please replace `use_container_width` with `width`.
`use_container_width` will be removed after 2025-12-31.
```

Puede ignorarse completamente. La app funciona con normalidad.

---

## Algoritmos implementados

| Algoritmo | Optimiza | Complejidad |
|---|---|---|
| **Dijkstra** | Distancia mínima en km | O((V+E) · log V) |
| **BFS** | Menor número de saltos | O(V + E) |
| **DFS** | Primer camino encontrado | O(V + E) |

Las distancias entre departamentos se calculan con la **fórmula Haversine** sobre las coordenadas reales de cada capital.

---

## Estructura del proyecto

```
📄 dijkstra_peru.py   ← archivo principal (único necesario)
📄 README.md          ← este archivo
```

---

## Versión de Python recomendada

```bash
python --version   # debe ser 3.8 o superior
```
