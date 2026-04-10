import math
import heapq
from collections import deque
import streamlit as st
import folium
from folium import plugins
from streamlit_folium import st_folium
import pandas as pd

# ─────────────────────────────────────────────────────────────────────────────
# DATOS GEOGRÁFICOS
# ─────────────────────────────────────────────────────────────────────────────
DEPARTAMENTOS = {
    "Amazonas":      (-6.2317,  -77.8694),
    "Ancash":        (-9.5269,  -77.5278),
    "Apurimac":      (-13.6389, -72.8814),
    "Arequipa":      (-16.4090, -71.5375),
    "Ayacucho":      (-13.1588, -74.2236),
    "Cajamarca":     (-7.1638,  -78.5003),
    "Callao":        (-12.0565, -77.1183),
    "Cusco":         (-13.5319, -71.9675),
    "Huancavelica":  (-12.7864, -74.9754),
    "Huanuco":       (-9.9306,  -76.2422),
    "Ica":           (-14.0675, -75.7286),
    "Junin":         (-12.0650, -75.2049),
    "La Libertad":   (-8.1116,  -79.0288),
    "Lambayeque":    (-6.7714,  -79.8409),
    "Lima":          (-12.0464, -77.0428),
    "Loreto":        (-3.7491,  -73.2538),
    "Madre de Dios": (-12.5933, -69.1891),
    "Moquegua":      (-17.1947, -70.9350),
    "Pasco":         (-10.6855, -76.2622),
    "Piura":         (-5.1945,  -80.6328),
    "Puno":          (-15.8402, -70.0219),
    "San Martin":    (-6.0342,  -76.9724),
    "Tacna":         (-18.0066, -70.2462),
    "Tumbes":        (-3.5669,  -80.4515),
    "Ucayali":       (-8.3791,  -74.5539),
}

FRONTERAS = [
    ("Tumbes",       "Piura"),
    ("Piura",        "Lambayeque"),
    ("Piura",        "Cajamarca"),
    ("Piura",        "Amazonas"),
    ("Lambayeque",   "Cajamarca"),
    ("Lambayeque",   "La Libertad"),
    ("Cajamarca",    "Amazonas"),
    ("Cajamarca",    "La Libertad"),
    ("Cajamarca",    "San Martin"),
    ("Amazonas",     "San Martin"),
    ("Amazonas",     "Loreto"),
    ("La Libertad",  "San Martin"),
    ("La Libertad",  "Ancash"),
    ("La Libertad",  "Huanuco"),
    ("San Martin",   "Loreto"),
    ("San Martin",   "Huanuco"),
    ("San Martin",   "Ucayali"),
    ("Loreto",       "Ucayali"),
    ("Ancash",       "Huanuco"),
    ("Ancash",       "Lima"),
    ("Ancash",       "Pasco"),
    ("Huanuco",      "Pasco"),
    ("Huanuco",      "Ucayali"),
    ("Huanuco",      "Junin"),
    ("Pasco",        "Junin"),
    ("Pasco",        "Lima"),
    ("Ucayali",      "Junin"),
    ("Ucayali",      "Madre de Dios"),
    ("Lima",         "Junin"),
    ("Lima",         "Ica"),
    ("Lima",         "Huancavelica"),
    ("Lima",         "Callao"),
    ("Callao",       "Lima"),
    ("Junin",        "Huancavelica"),
    ("Junin",        "Ayacucho"),
    ("Junin",        "Cusco"),
    ("Huancavelica", "Ica"),
    ("Huancavelica", "Ayacucho"),
    ("Ica",          "Ayacucho"),
    ("Ica",          "Arequipa"),
    ("Ayacucho",     "Apurimac"),
    ("Ayacucho",     "Cusco"),
    ("Ayacucho",     "Arequipa"),
    ("Apurimac",     "Cusco"),
    ("Apurimac",     "Arequipa"),
    ("Cusco",        "Madre de Dios"),
    ("Cusco",        "Puno"),
    ("Cusco",        "Arequipa"),
    ("Madre de Dios","Puno"),
    ("Arequipa",     "Puno"),
    ("Arequipa",     "Moquegua"),
    ("Puno",         "Moquegua"),
    ("Puno",         "Tacna"),
    ("Moquegua",     "Tacna"),
]

# ─────────────────────────────────────────────────────────────────────────────
# UTILIDADES
# ─────────────────────────────────────────────────────────────────────────────

def haversine(c1, c2):
    R = 6371.0
    lat1, lon1 = math.radians(c1[0]), math.radians(c1[1])
    lat2, lon2 = math.radians(c2[0]), math.radians(c2[1])
    a = math.sin((lat2-lat1)/2)**2 + math.cos(lat1)*math.cos(lat2)*math.sin((lon2-lon1)/2)**2
    return round(R * 2 * math.asin(math.sqrt(a)), 1)

def construir_grafo():
    g = {d: {} for d in DEPARTAMENTOS}
    for a, b in FRONTERAS:
        d = haversine(DEPARTAMENTOS[a], DEPARTAMENTOS[b])
        g[a][b] = d; g[b][a] = d
    return g

def reconstruir(previo, origen, destino, grafo):
    c, n = [], destino
    while n: c.append(n); n = previo[n]
    c.reverse()
    if not c or c[0] != origen: return [], []
    t = [(c[i], c[i+1], grafo[c[i]][c[i+1]]) for i in range(len(c)-1)]
    return c, t

def dijkstra(grafo, origen, destino):
    dist   = {n: float("inf") for n in grafo}; dist[origen] = 0
    previo = {n: None for n in grafo}
    heap   = [(0, origen)]; visitados = set(); pasos = []
    while heap:
        costo, nodo = heapq.heappop(heap)
        if nodo in visitados: continue
        visitados.add(nodo)
        upd = []
        for v, w in grafo[nodo].items():
            nc = costo + w
            if nc < dist[v]:
                dist[v] = nc; previo[v] = nodo
                heapq.heappush(heap, (nc, v)); upd.append(f"{v}({nc:.0f}km)")
        estado = "DESTINO" if nodo==destino else ("INICIO" if nodo==origen else "Visitado")
        pasos.append({
            "Paso": len(pasos)+1, "Nodo Actual": nodo,
            "Dist. Acum (km)": f"{costo:.0f}",
            "Vecinos Actualizados": ", ".join(upd) or "-",
            "Heap restante": len(heap), "Estado": estado,
        })
        if nodo == destino: break
    c, t = reconstruir(previo, origen, destino, grafo)
    return dist[destino], c, t, pasos

def bfs(grafo, origen, destino):
    cola = deque([(origen,[origen],0)]); visitados={origen}; pasos=[]
    while cola:
        nodo, cam, nivel = cola.popleft()
        nuevos = []
        for v in grafo[nodo]:
            if v not in visitados:
                visitados.add(v); cola.append((v, cam+[v], nivel+1)); nuevos.append(v)
        estado = "DESTINO" if nodo==destino else ("INICIO" if nodo==origen else "Visitado")
        pasos.append({
            "Paso": len(pasos)+1, "Nodo Actual": nodo,
            "Nivel (saltos)": nivel,
            "Vecinos Encolados": ", ".join(nuevos) or "-",
            "Cola restante": len(cola), "Estado": estado,
        })
        if nodo == destino:
            t = [(cam[i],cam[i+1],grafo[cam[i]][cam[i+1]]) for i in range(len(cam)-1)]
            return sum(x[2] for x in t), cam, t, pasos
    return float("inf"), [], [], pasos

def dfs(grafo, origen, destino):
    pila  = [(origen,[origen],{origen},0)]; pasos=[]; mejor=(float("inf"),[],[])
    while pila:
        nodo, cam, vis, prof = pila.pop()
        nuevos = []
        for v in grafo[nodo]:
            if v not in vis: nuevos.append(v); pila.append((v,cam+[v],vis|{v},prof+1))
        estado = "DESTINO" if nodo==destino else ("INICIO" if nodo==origen else "Explorado")
        pasos.append({
            "Paso": len(pasos)+1, "Nodo Actual": nodo,
            "Profundidad": prof,
            "Vecinos Apilados": ", ".join(nuevos) or "-",
            "Pila restante": len(pila), "Estado": estado,
        })
        if nodo == destino:
            t = [(cam[i],cam[i+1],grafo[cam[i]][cam[i+1]]) for i in range(len(cam)-1)]
            tot = sum(x[2] for x in t)
            if tot < mejor[0]: mejor=(tot,cam,t)
        if len(pasos) >= 200: break
    return mejor[0], mejor[1], mejor[2], pasos

# ─────────────────────────────────────────────────────────────────────────────
# PSEUDOCODIGO
# ─────────────────────────────────────────────────────────────────────────────
LOGICA = {
"Dijkstra": {
"desc": "Encuentra el camino de **menor costo acumulado** con una cola de prioridad (min-heap). Garantiza la solución óptima en grafos con pesos >= 0.",
"tiempo": "O((V + E) · log V)", "espacio": "O(V)",
"optimo": "SI — siempre la distancia minima", "completo": "SI",
"pseudo": """\
DIJKSTRA(grafo, origen, destino):
  dist[v] = INF  para todo v
  dist[origen] = 0
  heap = [(0, origen)]     -- cola de prioridad
  visitados = {}

  MIENTRAS heap no vacio:
    (costo, u) = EXTRAER_MIN(heap)

    SI u en visitados -> SALTAR
    AGREGAR u a visitados

    SI u == destino -> TERMINAR

    PARA CADA vecino v de u:
      nuevo = costo + peso(u, v)
      SI nuevo < dist[v]:
        dist[v] = nuevo
        previo[v] = u
        INSERTAR (nuevo, v) en heap

  RETORNAR reconstruir_camino(previo, destino)""",
"ventajas": "Optimo · Eficiente con heap · Grafos ponderados",
"desventajas": "No funciona con pesos negativos",
"usos": "GPS · Redes IP (OSPF) · Videojuegos (pathfinding)",
},
"BFS": {
"desc": "Explora el grafo **nivel por nivel** con una cola FIFO. Encuentra el camino de **menor numero de saltos**, sin considerar los pesos.",
"tiempo": "O(V + E)", "espacio": "O(V)",
"optimo": "PARCIAL — solo si pesos iguales", "completo": "SI",
"pseudo": """\
BFS(grafo, origen, destino):
  cola = [(origen, [origen], nivel=0)]  -- FIFO
  visitados = {origen}

  MIENTRAS cola no vacia:
    (nodo, camino, nivel) = DESENCOLAR(cola)

    SI nodo == destino:
      RETORNAR camino

    PARA CADA vecino de nodo:
      SI vecino NO en visitados:
        AGREGAR vecino a visitados
        ENCOLAR (vecino, camino+[vecino], nivel+1)

  RETORNAR sin solucion""",
"ventajas": "Simple · Optimo en grafos no ponderados",
"desventajas": "Ignora pesos → ruta puede ser mas larga en km",
"usos": "Redes sociales · Laberintos · Mapas sin pesos",
},
"DFS": {
"desc": "Explora el grafo **en profundidad** con una pila LIFO. Avanza hasta el fondo antes de retroceder. No garantiza ruta optima.",
"tiempo": "O(V + E)", "espacio": "O(V)",
"optimo": "NO — puede ser suboptimo", "completo": "SI (con control de visitados)",
"pseudo": """\
DFS(grafo, origen, destino):
  pila = [(origen, [origen], vis={origen})]  -- LIFO
  mejor = INF

  MIENTRAS pila no vacia:
    (nodo, camino, vis) = DESAPILAR(pila)

    SI nodo == destino:
      SI costo(camino) < mejor:
        mejor = camino
      CONTINUAR

    PARA CADA vecino de nodo:
      SI vecino NO en vis:
        APILAR (vecino, camino+[vecino], vis+{vecino})

  RETORNAR mejor""",
"ventajas": "Poco uso de memoria · Explora todo el espacio",
"desventajas": "No garantiza optimo · Puede ser lento",
"usos": "Deteccion de ciclos · Backtracking · Puzzles",
},
}

# ─────────────────────────────────────────────────────────────────────────────
# MAPA
# ─────────────────────────────────────────────────────────────────────────────
COLORES = {"Dijkstra": "#E63946", "BFS": "#00b4d8", "DFS": "#FF9800"}

def crear_mapa(grafo, camino, tramos, algoritmo, origen, destino):
    m = folium.Map(location=[-9.5,-75.0], zoom_start=6, tiles="CartoDB dark_matter")
    color = COLORES.get(algoritmo, "#E63946")
    en_ruta = set(camino)

    for a, b in FRONTERAS:
        folium.PolyLine(
            [DEPARTAMENTOS[a], DEPARTAMENTOS[b]],
            color="#4a5568", weight=1.5, opacity=0.4,
            tooltip=f"{a} -- {b}: {grafo[a][b]:.0f} km",
        ).add_to(m)

    if len(camino) > 1:
        coords = [DEPARTAMENTOS[n] for n in camino]
        folium.PolyLine(coords, color=color, weight=10, opacity=0.18).add_to(m)
        folium.PolyLine(coords, color=color, weight=4,  opacity=1.0 ).add_to(m)
        plugins.AntPath(coords, color=color, weight=3, opacity=0.85, delay=700, dash_array=[12,22]).add_to(m)

    for a, b, d in tramos:
        lm = ((DEPARTAMENTOS[a][0]+DEPARTAMENTOS[b][0])/2,
              (DEPARTAMENTOS[a][1]+DEPARTAMENTOS[b][1])/2)
        folium.Marker(lm, icon=folium.DivIcon(
            html=f'<div style="background:{color};color:white;font-size:10px;font-weight:bold;'
                 f'padding:2px 6px;border-radius:4px;white-space:nowrap">{d:.0f}km</div>',
            icon_size=(56,18), icon_anchor=(28,9))).add_to(m)

    for dep, (lat, lon) in DEPARTAMENTOS.items():
        pop = f"<b>{dep}</b><br>Vecinos: {', '.join(grafo[dep].keys())}"
        if dep == origen and dep in en_ruta:
            folium.Marker((lat,lon), popup=folium.Popup(pop,max_width=200),
                tooltip=f"ORIGEN: {dep}",
                icon=folium.Icon(color="green", icon="play", prefix="fa")).add_to(m)
        elif dep == destino and dep in en_ruta:
            folium.Marker((lat,lon), popup=folium.Popup(pop,max_width=200),
                tooltip=f"DESTINO: {dep}",
                icon=folium.Icon(color="red", icon="flag", prefix="fa")).add_to(m)
        elif dep in en_ruta:
            folium.CircleMarker((lat,lon), radius=9, color=color,
                fill=True, fill_color=color, fill_opacity=0.9,
                popup=folium.Popup(pop,max_width=200), tooltip=dep).add_to(m)
        else:
            folium.CircleMarker((lat,lon), radius=5, color="#718096",
                fill=True, fill_color="#2d3748", fill_opacity=0.8,
                popup=folium.Popup(pop,max_width=200), tooltip=dep).add_to(m)

    plugins.MiniMap(toggle_display=True, tile_layer="CartoDB positron").add_to(m)
    return m

# ─────────────────────────────────────────────────────────────────────────────
# STREAMLIT UI
# ─────────────────────────────────────────────────────────────────────────────
st.set_page_config(page_title="Dijkstra Peru", page_icon="🗺️", layout="wide")

st.markdown("""
<style>
@import url('https://fonts.googleapis.com/css2?family=Space+Grotesk:wght@400;600;700&family=JetBrains+Mono:wght@400;700&display=swap');
html,body,[class*="css"]{font-family:'Space Grotesk',sans-serif}
.hero{background:linear-gradient(135deg,#1a1a2e,#16213e 50%,#0f3460);
  border:1px solid #e6394625;border-radius:14px;padding:22px 28px;margin-bottom:16px;position:relative;overflow:hidden}
.hero::before{content:"";position:absolute;top:-50px;right:-50px;width:180px;height:180px;
  background:radial-gradient(circle,#e6394628,transparent 70%);border-radius:50%}
.hero h1{font-size:1.65rem;font-weight:700;color:#f7fafc;margin:0 0 4px;letter-spacing:-.5px}
.hero p{color:#a0aec0;font-size:.87rem;margin:0}
.badge{display:inline-block;background:#e6394615;border:1px solid #e6394640;color:#E63946;
  font-family:'JetBrains Mono',monospace;font-size:.71rem;padding:3px 10px;border-radius:20px;margin-top:8px}
.mcard{background:#1a202c;border:1px solid #2d3748;border-radius:10px;padding:12px 15px;margin-bottom:8px}
.mcard .lbl{color:#718096;font-size:.68rem;text-transform:uppercase;letter-spacing:1px;margin-bottom:3px}
.mcard .val{color:#f7fafc;font-size:1.4rem;font-weight:700;font-family:'JetBrains Mono',monospace}
.mcard .unt{color:#a0aec0;font-size:.72rem}
.rstep{display:flex;align-items:center;gap:8px;padding:8px 12px;background:#1a202c;
  border-radius:7px;margin-bottom:4px;border-left:3px solid var(--ac,#E63946)}
.rstep .dn{color:#e2e8f0;font-weight:600;font-size:.82rem}
.rstep .dd{color:#718096;font-size:.72rem;font-family:'JetBrains Mono',monospace}
.pseudo{background:#0d1117;border:1px solid #30363d;border-radius:10px;padding:14px 16px;
  margin:8px 0;font-family:'JetBrains Mono',monospace;font-size:.76rem;color:#c9d1d9;
  white-space:pre;overflow-x:auto;line-height:1.75}
.icard{background:#1a202c;border:1px solid #2d3748;border-radius:9px;padding:12px 14px;margin:6px 0}
.icard .il{color:#718096;font-size:.68rem;text-transform:uppercase;letter-spacing:1px;margin-bottom:3px}
.icard .iv{color:#e2e8f0;font-size:.83rem}
.tag2{display:inline-block;border-radius:5px;padding:2px 8px;font-size:.7rem;font-weight:700;margin:2px}
section[data-testid="stSidebar"]{background:#111827!important}
.stButton>button{background:linear-gradient(135deg,#E63946,#c62832)!important;color:white!important;
  border:none!important;border-radius:10px!important;font-weight:700!important;padding:12px 0!important;width:100%}
</style>
""", unsafe_allow_html=True)

GRAFO = construir_grafo()
DEPS  = sorted(DEPARTAMENTOS.keys())

if "res" not in st.session_state: st.session_state.res = None

# Hero
st.markdown("""
<div class="hero">
  <h1>🗺️ Dijkstra · Mapa del Peru</h1>
  <p>Ruta mas corta entre los 25 departamentos — geolocalización real + recorrido paso a paso</p>
  <span class="badge">Haversine · Dijkstra · BFS · DFS · Folium</span>
</div>
""", unsafe_allow_html=True)

# Sidebar
with st.sidebar:
    st.markdown("## Configuracion")
    st.markdown("---")
    origen    = st.selectbox("Origen",     DEPS, index=DEPS.index("Puno"))
    destino   = st.selectbox("Destino",    DEPS, index=DEPS.index("Lima"))
    algoritmo = st.selectbox("Algoritmo",  ["Dijkstra","BFS","DFS"])
    st.markdown("---")
    buscar = st.button("Encontrar Ruta Optima", use_container_width=True)
    st.markdown("---")
    st.markdown(f"**Nodos:** {len(DEPARTAMENTOS)}  |  **Aristas:** {len(FRONTERAS)}")
    st.markdown("**Peso:** km Haversine entre capitales")
    st.markdown("---")
    for al, col in COLORES.items():
        st.markdown(f'<span style="color:{col}">●</span> {al}', unsafe_allow_html=True)

if buscar:
    if origen == destino:
        st.error("Origen y destino deben ser distintos."); st.stop()
    fn = {"Dijkstra": dijkstra, "BFS": bfs, "DFS": dfs}[algoritmo]
    d, c, t, p = fn(GRAFO, origen, destino)
    st.session_state.res = dict(dist=d, camino=c, tramos=t, pasos=p,
                                algo=algoritmo, ori=origen, dst=destino)

if st.session_state.res:
    r = st.session_state.res
    dist=r["dist"]; camino=r["camino"]; tramos=r["tramos"]
    pasos=r["pasos"]; algo=r["algo"]; ori=r["ori"]; dst=r["dst"]
    color = COLORES.get(algo, "#E63946")

    # Badge cabecera
    st.markdown(f"""
    <div style="display:flex;align-items:center;gap:10px;margin-bottom:6px">
      <div style="width:11px;height:11px;border-radius:50%;background:{color}"></div>
      <span style="color:#e2e8f0;font-weight:600;font-size:.93rem">
        {algo} &nbsp;·&nbsp; {ori} → {dst} &nbsp;|&nbsp;
        <span style="color:{color};font-family:'JetBrains Mono',monospace">{dist:,.0f} km</span>
      </span>
    </div>""", unsafe_allow_html=True)

    # === MAPA GRANDE ===
    mapa = crear_mapa(GRAFO, camino, tramos, algo, ori, dst)
    st_folium(mapa, height=720, use_container_width=True)

    st.markdown("---")

    # === 3 COLUMNAS INFERIORES ===
    col1, col2, col3 = st.columns([1, 1.7, 1.5], gap="large")

    # COLUMNA 1 — Ruta
    with col1:
        st.markdown(f"### Ruta Optima")
        for lbl, val, unt in [
            ("Distancia Total", f"{dist:,.0f}", "km"),
            ("Departamentos",   str(len(camino)), "en la ruta"),
            ("Tramos",          str(len(tramos)), "conexiones"),
            ("Iteraciones",     str(len(pasos)),  "pasos del algoritmo"),
        ]:
            st.markdown(f"""
            <div class="mcard">
              <div class="lbl">{lbl}</div>
              <div class="val">{val}</div>
              <div class="unt">{unt}</div>
            </div>""", unsafe_allow_html=True)

        st.markdown("#### Camino detallado")
        acum = 0
        for i, dep in enumerate(camino):
            if i == 0:
                st.markdown(f"""
                <div class="rstep" style="--ac:#2ecc71">
                  <span style="color:#2ecc71">🟢</span>
                  <div><div class="dn">{dep}</div><div class="dd">ORIGEN · 0 km</div></div>
                </div>""", unsafe_allow_html=True)
            else:
                acum += tramos[i-1][2]
                ic  = "🔴" if i==len(camino)-1 else "📍"
                tag = "DESTINO" if i==len(camino)-1 else f"+{tramos[i-1][2]:.0f} km"
                st.markdown(f"""
                <div class="rstep" style="--ac:{color}">
                  <span style="color:{color}">{ic}</span>
                  <div><div class="dn">{dep}</div>
                  <div class="dd">{tag} · Acum: {acum:.0f} km</div></div>
                </div>""", unsafe_allow_html=True)

    # COLUMNA 2 — Tabla de recorrido
    with col2:
        st.markdown(f"### Recorrido del Algoritmo")
        st.caption(f"Cada fila = un paso que ejecuta {algo} internamente al explorar el grafo")

        df = pd.DataFrame(pasos)
        ruta_set = set(camino)

        def hl(row):
            n = row.get("Nodo Actual","")
            e = str(row.get("Estado",""))
            if "DESTINO" in e:
                return [f"background-color:#0d2b0d;color:#4ade80"]*len(row)
            if "INICIO" in e:
                return [f"background-color:#0d1f0d;color:#86efac"]*len(row)
            if n in ruta_set:
                return [f"background-color:#0d0d22;color:{color}"]*len(row)
            return [""]*len(row)

        st.dataframe(df.style.apply(hl, axis=1),
                     use_container_width=True, height=500, hide_index=True)

        total_vis = len(set(p["Nodo Actual"] for p in pasos))
        st.markdown(f"""
        <div style="display:flex;gap:7px;margin-top:8px;flex-wrap:wrap">
          <span class="tag2" style="background:#0d2b0d;color:#4ade80">
            {total_vis} nodos explorados
          </span>
          <span class="tag2" style="background:#0d0d22;color:{color}">
            {len(camino)} en ruta final
          </span>
          <span class="tag2" style="background:#1f1010;color:#f87171">
            {len(pasos)} iteraciones
          </span>
        </div>""", unsafe_allow_html=True)

    # COLUMNA 3 — Logica del algoritmo
    with col3:
        info = LOGICA[algo]
        st.markdown(f"### Logica: {algo}")
        st.markdown(info["desc"])

        for lbl, val in [
            ("Complejidad Tiempo", info["tiempo"]),
            ("Complejidad Espacio", info["espacio"]),
            ("Optimo",   info["optimo"]),
            ("Completo", info["completo"]),
        ]:
            st.markdown(f"""
            <div class="icard">
              <div class="il">{lbl}</div>
              <div class="iv" style="font-family:'JetBrains Mono',monospace;color:{color}">{val}</div>
            </div>""", unsafe_allow_html=True)

        st.markdown("#### Pseudocodigo")
        st.markdown(f'<div class="pseudo">{info["pseudo"]}</div>', unsafe_allow_html=True)

        for lbl, val in [
            ("Ventajas",    info["ventajas"]),
            ("Desventajas", info["desventajas"]),
            ("Casos de Uso",info["usos"]),
        ]:
            st.markdown(f"""
            <div class="icard">
              <div class="il">{lbl}</div>
              <div class="iv">{val}</div>
            </div>""", unsafe_allow_html=True)

else:
    # Estado inicial
    st_folium(crear_mapa(GRAFO,[],[],  "Dijkstra","",""), height=720, use_container_width=True)
    st.markdown("---")
    c1, c2, c3 = st.columns(3, gap="large")
    with c1:
        st.info("Selecciona origen, destino y algoritmo en el panel lateral, luego presiona Encontrar Ruta Optima.")
    with c2:
        st.markdown("#### Comparativa")
        st.markdown("""
| Algoritmo | Optimiza | Complejidad |
|-----------|----------|-------------|
| **Dijkstra** | Distancia min (km) | O((V+E)logV) |
| **BFS** | Menor saltos | O(V+E) |
| **DFS** | Primer camino | O(V+E) |""")
    with c3:
        st.markdown("#### Formula Haversine")
        st.latex(r"d=2R\arcsin\!\sqrt{\sin^2\!\tfrac{\Delta\phi}{2}+\cos\phi_1\cos\phi_2\sin^2\!\tfrac{\Delta\lambda}{2}}")
        st.caption("R = 6371 km")
